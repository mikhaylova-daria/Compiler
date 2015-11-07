//
// Created by nicolai on 03.11.15.
//

#include "TypeChecker.h"

extern void printTextPart(Location loc, std::ostream &out = std::cout);

void CTypeChecker::Visit(const CConstant *constant) {
    lastType = constant->Type->Type;
}

void CTypeChecker::Visit(const CBinaryExpression *binaryExpression) {
    binaryExpression->LeftExpr->Accept(this);
    TType leftType = lastType;
    binaryExpression->RightExpr->Accept(this);
    TType  rightType = lastType;
    if (leftType != rightType) {
        isCorrectTypes = false;
        printError(binaryExpression, "Different binary operation types");
    }
}

void CTypeChecker::Visit(const CNotExpression *notExpression) {
    notExpression->Expression->Accept(this);
    if (lastType != T_BOOL) {
        isCorrectTypes = false;
        printError(notExpression, "Expected binary expression");
    }
    lastType = T_BOOL;
}

void CTypeChecker::Visit(const CLengthExpression *lengthExpression) {

}

void CTypeChecker::Visit(const CExpressionList *expressionList) {
    while (expressionList != nullptr) {
        expressionList->Expression->Accept(this);
        expressionList = expressionList->ExpressionList;
    }
}

void CTypeChecker::Visit(const CIdentifier *identifier) {

}

void CTypeChecker::Visit(const CInvocation *invocation) {

}

void CTypeChecker::Visit(const CNewExpression *newExpression) {

}

void CTypeChecker::Visit(const CIntArrayNewExpression *intArrayNewExpression) {

}

void CTypeChecker::Visit(const CStatementList *statementList) {

}

void CTypeChecker::Visit(const CBracketStatement *bracketStatement) {

}

void CTypeChecker::Visit(const CIfStatement *ifStatement) {

}

void CTypeChecker::Visit(const CWhileStatement *whileStatement) {

}

void CTypeChecker::Visit(const CPrintStatement *printStatement) {

}

void CTypeChecker::Visit(const CAssignmentStatement *assignmentStatement) {

}

void CTypeChecker::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {

}

void CTypeChecker::Visit(const CVarDeclaration *varDeclaration) {

}

void CTypeChecker::Visit(const CVarDeclarationList *varDeclarationList) {

}

void CTypeChecker::Visit(const CBracketExpression *bracketExpression) {

}

void CTypeChecker::Visit(const CMethodArgumentsList *methodArgumentsList) {

}

void CTypeChecker::Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration) {

}

void CTypeChecker::Visit(const CMethodBodyDeclaration *methodBodyDeclaration) {

}

void CTypeChecker::Visit(const CMethodDeclaration *methodDeclaration) {

}

void CTypeChecker::Visit(const CMethodDeclarationList *methodDeclarationList) {

}

void CTypeChecker::Visit(const CClassDeclaration *classDeclaration) {

}

void CTypeChecker::Visit(const CMainClass *mainClass) {

}

void CTypeChecker::Visit(const CClassDeclarationList *classDeclarationList) {

}

void CTypeChecker::Visit(const CGoal *goal) {

}

void CTypeChecker::printError(const IToken *token, const std::string msg) {
    std::cerr << msg << std::endl;
    printTextPart(token->location, std::cerr);
}
