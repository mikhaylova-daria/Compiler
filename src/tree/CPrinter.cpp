//
// Created by daria on 27.10.15.
//

#include "CPrinter.h"

void CPrinter::Visit(const CAssignmentExpression *assignmentExpression) { ++countTab;--countTab;}
void CPrinter::Visit(const CBasicType *basicType) { ++countTab;--countTab;}
void CPrinter::Visit(const CBinaryExpression *binaryExpression) { ++countTab;--countTab;}
void CPrinter::Visit(const CClassType *classType) { ++countTab;--countTab;}
void CPrinter::Visit(const CConstant *constant) { ++countTab;--countTab;}
void CPrinter::Visit(const CExpressionList *expressionList) { ++countTab;--countTab;}
void CPrinter::Visit(const CIdentifier *identifier) { ++countTab;--countTab;}
void CPrinter::Visit(const CIfStatement *ifStatement) { ++countTab;--countTab;}
void CPrinter::Visit(const CIntArrayAssignmentExpression *arrayAssignmentExpression) { ++countTab;--countTab;}
void CPrinter::Visit(const CIntArrayNewExpression *intArrayNewExpression) { ++countTab;--countTab;}
void CPrinter::Visit(const CInvocation *invocation) { ++countTab;--countTab;}
void CPrinter::Visit(const CLengthExpression *lengthExpression) { ++countTab;--countTab;}
void CPrinter::Visit(const CNewExpression *newExpression) { ++countTab;--countTab;}
void CPrinter::Visit(const CNotExpression *notExpression) { ++countTab;--countTab;}
void CPrinter::Visit(const CPrintStatement *printStatement) { ++countTab;--countTab;}
void CPrinter::Visit(const CStatementList *statementList) { ++countTab;--countTab;}
void CPrinter::Visit(const CVarDeclaration *varDeclaration) { ++countTab;--countTab;}
void CPrinter::Visit(const CVarDeclarationList *varDeclarationList) { ++countTab;--countTab;}
void CPrinter::Visit(const CWhileStatement *whileStatement) { ++countTab;--countTab;}
