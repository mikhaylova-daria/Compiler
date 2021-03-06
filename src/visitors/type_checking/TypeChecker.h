//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_TYPECHECKER_H
#define MINIJAVACOMPILER_TYPECHECKER_H

#include "../../tree/MinijavaTree.h"
#include "Table.h"

using namespace SymbolTable;

extern void printTextPart(Location loc, std::ostream &out);

class CTypeChecker : public IVisitor {
public:
    CTypeChecker(const CTable& table, CStorage& storage) : table(table), storage(storage) {}

    virtual void Visit(const CConstant *constant);
    virtual void Visit(const CVariable* variable);
    virtual void Visit(const CType* type);
    virtual void Visit(const CBinaryExpression *binaryExpression);
    virtual void Visit(const CNotExpression *notExpression);
    virtual void Visit(const CLengthExpression *lengthExpression);
    virtual void Visit(const CExpressionList *expressionList);
    virtual void Visit(const CIdentifier *identifier);
    virtual void Visit(const CInvocation *invocation);
    virtual void Visit(const CNewExpression *newExpression);
    virtual void Visit(const CIntArrayNewExpression *intArrayNewExpression);
    virtual void Visit(const CStatementList *statementList);
    virtual void Visit(const CBracketStatement *bracketStatement);
    virtual void Visit(const CIfStatement *ifStatement);
    virtual void Visit(const CWhileStatement *whileStatement);
    virtual void Visit(const CPrintStatement *printStatement);
    virtual void Visit(const CAssignmentStatement *assignmentStatement);
    virtual void Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement);
    virtual void Visit(const CVarDeclaration *varDeclaration);
    virtual void Visit(const CVarDeclarationList *varDeclarationList);
    virtual void Visit(const CBracketExpression *bracketExpression);
    virtual void Visit(const CMethodArgumentsList *methodArgumentsList);
    virtual void Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration);
    virtual void Visit(const CMethodBodyDeclaration *methodBodyDeclaration);
    virtual void Visit(const CMethodDeclaration *methodDeclaration);
    virtual void Visit(const CMethodDeclarationList *methodDeclarationList);
    virtual void Visit(const CClassDeclaration *classDeclaration);
    virtual void Visit(const CMainClass *mainClass);
    virtual void Visit(const CClassDeclarationList *classDeclarationList);
    virtual void Visit(const CGoal *goal);

    bool IsError() {
        return isError;
    }

private:
    void processError(const std::string& reason, const IToken* token) {
        isError = true;
        std::cerr << "Type error: " << reason << std::endl;
        std::cerr << "..Line " << token->location.firstLine << " Position " << token->location.firstColumn << std::endl;
        printTextPart(token->location, std::cerr);
    }

    template<class T, const CSymbol* T::*NAME>
    typename std::vector<T>::const_iterator find(const std::vector<T> &list, const CSymbol* symbol) {
        typename std::vector<T>::const_iterator it;
        for (it = list.begin(); it != list.end(); ++it) {
            if ((*it).*NAME == symbol) {
                break;
            }
        }
        return it;
    }

    template<class T, const CSymbol* T::*NAME>
    bool isContain(const std::vector<T> &list, const CSymbol* symbol) {
        return find<T,NAME>(list, symbol) != list.end();
    }

    bool isCorrectInvocation(const std::vector<CVarInfo>& methodSignature, const std::vector<CTypeInfo>& typeInfoList) {
        // у метода неявный this в начале, который уже добавлен явно для упрощения проверки типов
        assert(methodSignature.size() > 0 && methodSignature[0].VarName->GetName() == "this");
        if (methodSignature.size() != 1 + typeInfoList.size()) {
            return false;
        }
        for (size_t i = 1; i < methodSignature.size(); i++) {
            if (methodSignature[i].TypeInfo != typeInfoList[i - 1]) {
                // возможно, работает полиморфизм. идем по родителям аргумента
                if (methodSignature[i].TypeInfo.VarType == TType::T_CLASS) {
                    const CSymbol* classSymbol = typeInfoList[i - 1].TypeName;
                    for (size_t j = 0; j <= table.Classes.size(); j++) {
                        auto it = find<CClassInfo,&CClassInfo::Name>(table.Classes, classSymbol);
                        if (it == table.Classes.end()) {
                            return false;
                        }
                        classSymbol = it->Base;
                        if (classSymbol == methodSignature[i].TypeInfo.TypeName) {
                            break;
                        }
                    }
                    if (classSymbol != methodSignature[i].TypeInfo.TypeName) {
                        return false;
                    }
                } else {
                    return false;
                }
            }
        }
        return true;
    }

    bool isCyclicInheritance(const CSymbol* classSymbol) {
        auto classIterator = find<CClassInfo,&CClassInfo::Name>(table.Classes, classSymbol);
        size_t counter = 0;
        while (classSymbol != nullptr && classIterator != table.Classes.end() && counter <= table.Classes.size()) {
            classSymbol = classIterator->Base;
            classIterator = find<CClassInfo,&CClassInfo::Name>(table.Classes, classSymbol);
            assert(!(classSymbol == nullptr && classIterator != table.Classes.end()));
            counter++;
        }
        return counter > table.Classes.size();
    }

    CClassInfo currentClass;
    CMethodInfo currentMethod;
    CTypeInfo lastType;
    std::vector<CTypeInfo> lastTypeList;
    const CTable& table;
    CStorage &storage;
    bool isError = false;
};


#endif //MINIJAVACOMPILER_TYPECHECKER_H
