#include <cstdio>
#include <fstream>
#include <iostream>
#include "symbol/Symbol.h"
#include "tree/MinijavaTree.h"
#include "visitors/CPrettyPrinter.hpp"
#include "visitors/type_checking/TypeChecker.h"
#include "visitors/type_checking/SymbolTableBuilder.h"
#include "visitors/CIRTreeBuilder.h"
#include "visitors/CPrinter2.hpp"

Symbol::CStorage globalStorage;
extern std::shared_ptr<CGoal> Goal;
#include "visitors/IRtree/CIRTreePrinter.hpp"
#include "visitors/IRtree/CIRTreeCanonizator.h"
#include "visitors/IRtree/CIRTreeLinearizator.h"
#include "visitors/IRtree/CIRTreeJumpOptimizer.h"
#include "visitors/IRtree/CIRTreeCodeGenerator.h"
#include "Instruction/Instruction.h"
#include "Instruction/InstructionOperations.hpp"
#include "Instruction/RegisterMapper.h"
#include "visitors/IRtree/CIRTreeLin.h"

extern "C" {
    int yylex();
}

extern "C" FILE* yyin;

extern int yyparse();

using namespace std;

vector<string> text;


void printTextPart(Location loc, ostream &out = std::cout)
{
    loc.firstColumn--; loc.firstLine--; loc.lastColumn--; loc.lastLine--;
    if (loc.firstLine == loc.lastLine) {
        out << text[loc.firstLine].substr(loc.firstColumn, loc.lastColumn - loc.firstColumn) << endl;
    } else {
        //cout << text[loc.firstColumn].size() << endl;
        for (int i = 0; i < loc.firstColumn; i++)
            out << ' ';
        out << text[loc.firstLine].substr(loc.firstColumn, text[loc.firstLine].size() - loc.firstColumn) << endl;
        for (int i = loc.firstLine + 1; i < loc.lastLine; i++)
            out << text[i] << endl;
        out << text[loc.lastLine].substr(0, loc.lastColumn) << endl;
    }
}

void printError(Location location, const char *s)
{
    std::cerr << "error in position (" << location.lastLine << ' ' << location.firstColumn << ' ';
    std::cerr << location.lastLine << ' ' << location.lastColumn << "): " << s << " : ";
    printTextPart(location, std::cerr);
}


int main(int argc, const char* argv[])
{
    ifstream in(argv[1]);
    string line;
    while (getline(in, line))
        text.push_back(line);

    yyin = fopen(argv[1], "r");
    yyparse();
    //CPrettyPrinter printer2;
    //printer2.Visit(Goal.get());
    CPrinter2 astPrinter;
    astPrinter.Visit(Goal.get());
    std::cout << "--- end ---" << std::endl;
    CTable table;
    CSymbolTableBuilder symbolTableBuilder(table, globalStorage);
    symbolTableBuilder.Visit(Goal.get());
    if (symbolTableBuilder.IsError()) {
        std::cout << "type error" << std::endl;
        return -1;
    }
    CTypeChecker typeChecker(table, globalStorage);
    typeChecker.Visit(Goal.get());
    if (typeChecker.IsError()) {
        std::cout << "type error" << std::endl;
        return -1;
    }
    CIRTreeBuilder irTreeBuilder(globalStorage, table);
    irTreeBuilder.Visit(Goal.get());
    std::cout << "built IRTtree" << std::endl;
	CIRTreePrinter firstPrinter("tree_first.gv");
    CIRTreePrinter canonicalPrinter("tree_canon.gv");
    CIRTreePrinter linearPrinter("tree_linear.gv");
    CIRTreePrinter optPrinter("tree_opt.gv");
    CIRTreeCanonizator canonizator(globalStorage);

    std::vector<CIRTreeBuilder::Function> functions = irTreeBuilder.functions;
    for (int i = 0; i < functions.size(); i++) {
        std::cout << functions[i].name->GetName() << std::endl;
        functions[i].root->Accept(&firstPrinter);
    }
    for( int i = 0; i < functions.size(); i++) {
        std::cout << functions[i].name->GetName() << std::endl;
        functions[i].root->Accept(&canonizator);
        functions[i].root = canonizator.GetRoot();
    }
    for( int i = 0; i < functions.size(); i++) {
        functions[i].root->Accept(&canonicalPrinter);
    }

    CIRTreeLin linearizatior;
    std::vector<std::shared_ptr<StatementList>> stmLists;
    for( int i = 0; i < functions.size(); i++) {
        stmLists.push_back(linearizatior.Linearize(functions[i].root));
        stmLists.back()->Accept(&linearPrinter);
    }
    CIRTreeJumpOptimizer optimizer(globalStorage);
    for( int i = 0; i < functions.size(); i++) {
        stmLists[i] = optimizer.Optimize(stmLists[i]);
        stmLists[i]->Accept(&optPrinter);
    }
    std::vector<CodeGeneration::CCode> codes;
    std::vector<CodeGeneration::CCode> mappedCodes;
    CodeGeneration::CGenerator generator(globalStorage);
    CodeGeneration::CRegisterMapper mapper(generator);
    CIRTreeCodeGenerator codeGenerator(generator, 4);
    ofstream codeOut("code.txt");
    ofstream mappedCodeOut("code_mapped.txt");
    ofstream codeFinal("code_final.s");

    ifstream templ("./assembly_functions/template.txt");
    std::string str;
    while( getline(templ, str) ) {
        codeFinal << str << endl;
    }

    for( int i = 0; i < stmLists.size(); i++) {
        codes.push_back(codeGenerator.Generate(stmLists[i], functions[i].Arguments));
        CodeGeneration::PrintCode(codes.back(), codeOut);
        std::vector<CTemp*> args;
        for( auto& arg : functions[i].Arguments ) {
            args.push_back(arg.get());
        }
        cout << functions[i].name->GetName() << ": Map register started" << endl;
        auto mapResult = mapper.Map(codes.back(), args);
        cout << functions[i].name->GetName() << ": Map register finished" << endl;
        mappedCodes.push_back(mapResult.Code);
        CodeGeneration::PrintCode(mappedCodes.back(), mappedCodeOut, mapResult.TempToReg);

        CodeGeneration::CGenerator::CFunctionGenerateArg arg;
        arg.tempMap = mapResult.TempToReg;
        arg.args = functions[i].Arguments;
        //arg.all = mapResult.All;
        arg.onStack.insert(mapResult.OnStack.begin(), mapResult.OnStack.end());
        CodeGeneration::CCode finCode = generator.GenerateFunctionFinalCode(mappedCodes.back(), arg,
                                                                            functions[i].name->GetName());
        CodeGeneration::PrintCode(finCode, codeFinal, arg.tempMap);
    }
    return 0;
}
