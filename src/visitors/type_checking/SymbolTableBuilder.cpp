//
// Created by nicolai on 03.11.15.
//

#include "SymbolTableBuilder.h"

CSymbolTableBuilder::~CSymbolTableBuilder() {

}

void CSymbolTableBuilder::Visit(const CType*) {
}

void CSymbolTableBuilder::Visit(const CVariable* variable) {
    variable->Identifier->Accept(this);
}

void CSymbolTableBuilder::Visit(const CConstant *constant) {
    constant->Type->Accept(this);
}

void CSymbolTableBuilder::Visit(const CBinaryExpression *binaryExpression) {
    binaryExpression->LeftExpr->Accept(this);
    binaryExpression->RightExpr->Accept(this);
}

void CSymbolTableBuilder::Visit(const CNotExpression *notExpression) {
    notExpression->Expression->Accept(this);
}

void CSymbolTableBuilder::Visit(const CLengthExpression *lengthExpression) {
    lengthExpression->Expression->Accept(this);
}

void CSymbolTableBuilder::Visit(const CExpressionList *expressionList) {
    expressionList->Expression->Accept(this);
    if (expressionList->ExpressionList != nullptr) {
        expressionList->ExpressionList->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CIdentifier*) {

}

void CSymbolTableBuilder::Visit(const CInvocation *invocation) {
    invocation->Expression->Accept(this);
    invocation->Identifier->Accept(this);
}

void CSymbolTableBuilder::Visit(const CNewExpression *newExpression) {
    newExpression->Id->Accept(this);
}

void CSymbolTableBuilder::Visit(const CIntArrayNewExpression *intArrayNewExpression) {
    intArrayNewExpression->Expression->Accept(this);
}

void CSymbolTableBuilder::Visit(const CStatementList *statementList) {
    statementList->Statement->Accept(this);
    if (statementList->StatementList != nullptr) {
        statementList->StatementList->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CBracketStatement *bracketStatement) {
    if (bracketStatement->StatementList != nullptr) {
        bracketStatement->StatementList->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CIfStatement *ifStatement) {
    ifStatement->Expression->Accept(this);
    ifStatement->TrueStatement->Accept(this);
    ifStatement->FalseStatement->Accept(this);
}

void CSymbolTableBuilder::Visit(const CWhileStatement *whileStatement) {
    whileStatement->Expression->Accept(this);
    whileStatement->Statement->Accept(this);
}

void CSymbolTableBuilder::Visit(const CPrintStatement *printStatement) {
    printStatement->Expression->Accept(this);
}

void CSymbolTableBuilder::Visit(const CAssignmentStatement *assignmentStatement) {
    assignmentStatement->Expression->Accept(this);
    assignmentStatement->Variable->Accept(this);
}

void CSymbolTableBuilder::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {
    intArrayAssignmentStatement->Variable->Accept(this);
    intArrayAssignmentStatement->Expression->Accept(this);
    intArrayAssignmentStatement->Index->Accept(this);
}

void CSymbolTableBuilder::Visit(const CVarDeclaration *varDeclaration) {
    varDeclaration->Type->Accept(this);

    CTypeInfo typeInfo = CTypeInfo(varDeclaration->Type->Name, varDeclaration->Type->Type);
    CVarInfo varInfo(varDeclaration->Identifier->Symbol, typeInfo);//lastType);
    for (int i = 0; i < currentValList.size(); i++ ) {
        if (varInfo.VarName == currentValList[i].VarName) {
            processError("redefinition ", varDeclaration);
        }
    }
    currentValList.push_back(varInfo);

    varDeclaration->Identifier->Accept(this);
}

void CSymbolTableBuilder::Visit(const CVarDeclarationList *varDeclarationList) {
    varDeclarationList->VarDeclaration->Accept(this);
    if (varDeclarationList->Next != nullptr) {
        varDeclarationList->Next->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CBracketExpression *bracketExpression) {
    bracketExpression->Expression->Accept(this);
}

void CSymbolTableBuilder::Visit(const CMethodArgumentsList *methodArgumentsList) {
    methodArgumentsList->VarDeclaration->Accept(this);
    if (methodArgumentsList->Next != nullptr) {
        methodArgumentsList->Next->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration) {
    if (methodHeaderDeclaration->MethodArgumentList != nullptr) {
        methodHeaderDeclaration->MethodArgumentList->Accept(this);
    }
    methodHeaderDeclaration->MethodName->Accept(this);
    methodHeaderDeclaration->ReturnType->Accept(this);
}

void CSymbolTableBuilder::Visit(const CMethodBodyDeclaration *methodBodyDeclaration) {
    methodBodyDeclaration->ReturnExpression->Accept(this);
    if (methodBodyDeclaration->VarDeclarationList != nullptr) {
        methodBodyDeclaration->VarDeclarationList->Accept(this);
    }
    if (methodBodyDeclaration->StatementList != nullptr) {
        methodBodyDeclaration->StatementList->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CMethodDeclaration *methodDeclaration) {
    CType* returnType = methodDeclaration->MethodHeaderDeclaration->ReturnType;
    CTypeInfo returnTypeInfo = CTypeInfo(returnType->Name, returnType->Type);
    currentMethod = CMethodInfo(methodDeclaration->MethodHeaderDeclaration->MethodName->Symbol, returnTypeInfo);

    currentMethod.Arguments.swap(currentValList);
    currentValList.push_back(CVarInfo(storage.Get("this"), CTypeInfo(currentClass.Name, TType::T_CLASS)));
    methodDeclaration->MethodHeaderDeclaration->Accept(this);
    currentMethod.Arguments.swap(currentValList);

    currentMethod.Vars.swap(currentValList);
    methodDeclaration->MethodBodyDeclaration->Accept(this);
    currentMethod.Vars.swap(currentValList);

    currentClass.Methods.push_back(currentMethod);
}

void CSymbolTableBuilder::Visit(const CMethodDeclarationList *methodDeclarationList) {
    methodDeclarationList->MethodDeclaration->Accept(this);
    if (methodDeclarationList->MethodDeclarationList != nullptr) {
        methodDeclarationList->MethodDeclarationList->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CClassDeclaration *classDeclaration) {

    if (classDeclaration->BaseClassName != nullptr) {
        currentClass = CClassInfo(classDeclaration->ClassName->Symbol, classDeclaration->BaseClassName->Symbol);
        classDeclaration->BaseClassName->Accept(this);
    } else {
        currentClass = CClassInfo(classDeclaration->ClassName->Symbol, nullptr);
    }
    classDeclaration->ClassName->Accept(this);
    if (classDeclaration->VarDeclarationList != nullptr) {
        currentClass.Vars.swap(currentValList);
        classDeclaration->VarDeclarationList->Accept(this);
        currentClass.Vars.swap(currentValList);
    }
    // this первый аргумент метода, а не поле класса
    //currentClass.Vars.push_back(CVarInfo(storage.Get("this"), CTypeInfo(currentClass.Name, TType::T_CLASS)));
    if (classDeclaration->MethodDeclarationList != nullptr) {
        classDeclaration->MethodDeclarationList->Accept(this);
    }

    table.Classes.push_back(currentClass);
}

void CSymbolTableBuilder::Visit(const CMainClass *mainClass) {
    mainClass->ClassName->Accept(this);
    mainClass->ArgumentName->Accept(this);
    mainClass->MainFunctionStatement->Accept(this);
    //CClassInfo mainClassInfo(mainClass->ClassName->Symbol, nullptr);
    //CMethodInfo mainMethodInfo(storage.Get("#main"))
}

void CSymbolTableBuilder::Visit(const CClassDeclarationList *classDeclarationList) {
    classDeclarationList->ClassDeclaration->Accept(this);
    if (classDeclarationList->ClassDeclarationList != nullptr) {
        classDeclarationList->ClassDeclarationList->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CGoal *goal) {
    goal->MainClass->Accept(this);
    if (goal->ClassDeclarationList != nullptr) {
        goal->ClassDeclarationList->Accept(this);
    }
}
