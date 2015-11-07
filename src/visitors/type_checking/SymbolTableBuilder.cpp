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
    if (expressionList != nullptr) {
        expressionList->Expression->Accept(this);
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

}

void CSymbolTableBuilder::Visit(const CBracketStatement *bracketStatement) {

}

void CSymbolTableBuilder::Visit(const CIfStatement *ifStatement) {

}

void CSymbolTableBuilder::Visit(const CWhileStatement *whileStatement) {

}

void CSymbolTableBuilder::Visit(const CPrintStatement *printStatement) {

}

void CSymbolTableBuilder::Visit(const CAssignmentStatement *assignmentStatement) {

}

void CSymbolTableBuilder::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {

}

void CSymbolTableBuilder::Visit(const CVarDeclaration *varDeclaration) {

}

void CSymbolTableBuilder::Visit(const CVarDeclarationList *varDeclarationList) {

}

void CSymbolTableBuilder::Visit(const CBracketExpression *bracketExpression) {

}

void CSymbolTableBuilder::Visit(const CMethodArgumentsList *methodArgumentsList) {

}

void CSymbolTableBuilder::Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration) {

}

void CSymbolTableBuilder::Visit(const CMethodBodyDeclaration *methodBodyDeclaration) {

}

void CSymbolTableBuilder::Visit(const CMethodDeclaration *methodDeclaration) {

}

void CSymbolTableBuilder::Visit(const CMethodDeclarationList *methodDeclarationList) {

}

void CSymbolTableBuilder::Visit(const CClassDeclaration *classDeclaration) {

}

void CSymbolTableBuilder::Visit(const CMainClass *mainClass) {

}

void CSymbolTableBuilder::Visit(const CClassDeclarationList *classDeclarationList) {

}

void CSymbolTableBuilder::Visit(const CGoal *goal) {

}
