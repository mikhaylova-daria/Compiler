//
// Created by daria on 27.10.15.
//

#include <iostream>
#include "CPrinter.h"

void CPrinter::Visit(const CAssignmentExpression *assignmentExpression) {
    std::cout<<"CAssignmentExpression"<<std::endl;
} 
void CPrinter::Visit(const CBasicType *basicType) {
    std::cout<<"CBasicType"<<std::endl;
}
void CPrinter::Visit(const CBinaryExpression *binaryExpression) {
    std::cout<<"CBinaryExpression"<<std::endl;
}
void CPrinter::Visit(const CClassType *classType) {
    std::cout<<"CClassType"<<std::endl;
}
void CPrinter::Visit(const CConstant *constant) {
    std::cout<<"CConstant"<<std::endl;
}
void CPrinter::Visit(const CExpressionList *expressionList) {
    std::cout<<"CExpressionList"<<std::endl;
}
void CPrinter::Visit(const CIdentifier *identifier) {
    std::cout<<"CIdentifier"<<std::endl;
}
void CPrinter::Visit(const CIfStatement *ifStatement) {
    std::cout<<"CIfStatement"<<std::endl;
}
void CPrinter::Visit(const CIntArrayAssignmentExpression *arrayAssignmentExpression) {
    std::cout<<"CIntArrayAssignmentExpression"<<std::endl;
}
void CPrinter::Visit(const CIntArrayNewExpression *intArrayNewExpression) {
    std::cout<<"CIntArrayNewExpression"<<std::endl;
}
void CPrinter::Visit(const CInvocation *invocation) {
    std::cout<<"CInvocation"<<std::endl;
}
void CPrinter::Visit(const CLengthExpression *lengthExpression) {
    std::cout<<"CLengthExpression"<<std::endl;
}
void CPrinter::Visit(const CNewExpression *newExpression) {
    std::cout<<"CNewExpression"<<std::endl;
}
void CPrinter::Visit(const CNotExpression *notExpression) {
    std::cout<<"CNotExpression"<<std::endl;
}
void CPrinter::Visit(const CPrintStatement *printStatement) {
    std::cout<<"CPrintStatement"<<std::endl;
}
void CPrinter::Visit(const CStatementList *statementList) {
    std::cout<<"CStatementList"<<std::endl;
}
void CPrinter::Visit(const CVarDeclaration *varDeclaration) {
    std::cout<<"CVarDeclaration"<<std::endl;
}
void CPrinter::Visit(const CVarDeclarationList *varDeclarationList) {
    std::cout<<"CVarDeclarationLis"<<std::endl;
}
void CPrinter::Visit(const CWhileStatement *whileStatement) {
    std::cout<<"CWhileStatement"<<std::endl;
}
