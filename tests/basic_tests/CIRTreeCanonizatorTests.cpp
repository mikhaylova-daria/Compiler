//
// Created by Ава Катушка on 22.03.16.
//
#include "gtest/gtest.h"
//#include <cstdio>
//#include <fstream>
//#include <iostream>
//#include "../../src/symbol/Symbol.h"
//#include "../../src/tree/MinijavaTree.h"
//#include "../../src/visitors/CPrettyPrinter.hpp"
//#include "../../src/visitors/type_checking/TypeChecker.h"
//#include "../../src/visitors/type_checking/SymbolTableBuilder.h"
//#include "../../src/visitors/CIRTreeBuilder.h"
//#include "../../src/visitors/CPrinter2.hpp"
//#include "../../src/tree/Declaration.h"
//
//Symbol::CStorage globalStorage;
//extern std::shared_ptr < CGoal > Goal;
//
//#include "../../src/visitors/IRtree/CIRTreePrinter.hpp"
//#include "../../src/visitors/IRtree/CIRTreeCanonizator.h"
//
//using namespace std;
//
//extern "C" {
//int yylex();
//}
//
//extern "C" FILE* yyin;
//
//extern int yyparse();
//
//using namespace std;
//
//vector<string> text;


TEST( Main_TestName_Test, Main_TestName_Test_M_Test ) {
//	string arg = "../programms/factorial.mj";
//	ifstream in( arg );
//	string line;
//	while ( getline( in, line ))
//		text.push_back( line );
//
//	yyin = fopen( arg.c_str(), "r" );
//	yyparse();
//	//CPrettyPrinter printer2;
//	//printer2.Visit(Goal.get());
//	CPrinter2 astPrinter;
//	astPrinter.Visit( Goal.get());
//	std::cout << "--- end ---" << std::endl;
//	CTable table;
//	CSymbolTableBuilder symbolTableBuilder( table, globalStorage );
//	symbolTableBuilder.Visit( Goal.get());
//	ASSERT_FALSE(symbolTableBuilder.IsError());
//	CTypeChecker typeChecker( table, globalStorage );
//	typeChecker.Visit( Goal.get());
//	ASSERT_FALSE(typeChecker.IsError());
//	CIRTreeBuilder irTreeBuilder( globalStorage, table );
//	irTreeBuilder.Visit( Goal.get());
//	std::cout << "built IRTtree" << std::endl;
//	CIRTreePrinter firstPrinter( "tree_first.gv" );
//	CIRTreePrinter canonicalPrinter( "tree_canon.gv" );
//	CIRTreeCanonizator canonizator( globalStorage );
//	for ( int i = 0; i < irTreeBuilder.functions.size(); i++ ) {
//		std::cout << irTreeBuilder.functions[ i ].name->GetName() << std::endl;
//		irTreeBuilder.functions[ i ].root->ToStm()->Accept( &canonizator );
//		canonizator.GetRoot()->Accept( &canonicalPrinter );
//		irTreeBuilder.functions[ i ].root->ToStm()->Accept( &firstPrinter );
//	}
}


