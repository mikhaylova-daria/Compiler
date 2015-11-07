//
// Created by nicolai on 03.11.15.
//

#include "SymbolTableBuilder.h"

CSymbolTableBuilder::~CSymbolTableBuilder() {

}

void CSymbolTableBuilder::Visit(const CType* type) {
    lastType = CTypeInfo(type->Name, type->Type);
}

void CSymbolTableBuilder::Visit(const CVariable* variable) {

}

void CSymbolTableBuilder::Visit(const CConstant *constant) {
    lastType = CTypeInfo(constant->Type->Name, constant->Type->Type);
}

void CSymbolTableBuilder::Visit(const CBinaryExpression *binaryExpression) {

}

void CSymbolTableBuilder::Visit(const CNotExpression *notExpression) {

}

void CSymbolTableBuilder::Visit(const CLengthExpression *lengthExpression) {

}

void CSymbolTableBuilder::Visit(const CExpressionList *expressionList) {
    expressionList->Expression->Accept(this);
    if (expressionList->ExpressionList != nullptr) {
        expressionList->ExpressionList->Accept(this);
    }
}

void CSymbolTableBuilder::Visit(const CIdentifier *identifier) {

}

void CSymbolTableBuilder::Visit(const CInvocation *invocation) {

}

void CSymbolTableBuilder::Visit(const CNewExpression *newExpression) {

}

void CSymbolTableBuilder::Visit(const CIntArrayNewExpression *intArrayNewExpression) {

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
    assignmentStatement->Identifier->Accept(this);
}

void CSymbolTableBuilder::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {
    intArrayAssignmentStatement->Identifier->Accept(this);
    intArrayAssignmentStatement->Expression->Accept(this);
    intArrayAssignmentStatement->Index->Accept(this);
}

void CSymbolTableBuilder::Visit(const CVarDeclaration *varDeclaration) {
    varDeclaration->Type->Accept(this);

    CVarInfo varInfo(varDeclaration->Identifier->Symbol, lastType);
    if (!checkVarDuplicateDefinition(currentValList, varInfo)) {
        processError("duplicate variable declaration", varDeclaration);
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
    currentMethod = CMethodInfo(methodDeclaration->MethodHeaderDeclaration->MethodName->Symbol);
    currentMethod.Arguments.swap(currentValList);
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
    currentClass = CClassInfo(classDeclaration->ClassName->Symbol);

    if (classDeclaration->BaseClassName != nullptr) {
        classDeclaration->BaseClassName->Accept(this);
    }
    classDeclaration->ClassName->Accept(this);
    if (classDeclaration->VarDeclarationList != nullptr) {
        currentClass.Vars.swap(currentValList);
        classDeclaration->VarDeclarationList->Accept(this);
        currentClass.Vars.swap(currentValList);
    }
    if (classDeclaration->MethodDeclarationList != nullptr) {
        classDeclaration->MethodDeclarationList->Accept(this);
    }

    table.Classes.push_back(currentClass);
}

void CSymbolTableBuilder::Visit(const CMainClass *mainClass) {
    mainClass->ClassName->Accept(this);
    mainClass->MainFunctionStatement->Accept(this);
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
