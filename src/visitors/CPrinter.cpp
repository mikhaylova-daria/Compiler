//
// Created by daria on 27.10.15.
//

#include <iostream>
#include "CPrinter.h"


void print( const std::string& what ) {
	std::cout << what << std::endl;
}

void CPrinter::Visit( const CBasicType* basicType ) {
	print( basicType->GetName());
}

void CPrinter::Visit( const CBinaryExpression* binaryExpression ) {
	print( binaryExpression->GetName());
}

void CPrinter::Visit( const CClassType* classType ) {
	print( classType->GetName());
}

void CPrinter::Visit( const CConstant* constant ) {
	print( constant->GetName());
}

void CPrinter::Visit( const CExpressionList* expressionList ) {
	print( expressionList->GetName());
}

void CPrinter::Visit( const CIdentifier* identifier ) {
	print( identifier->GetName());
}

void CPrinter::Visit( const CIfStatement* ifStatement ) {
	print( ifStatement->GetName());
}

void CPrinter::Visit( const CIntArrayNewExpression* intArrayNewExpression ) {
	print( intArrayNewExpression->GetName());
}

void CPrinter::Visit( const CInvocation* invocation ) {
	print( invocation->GetName());
}

void CPrinter::Visit( const CLengthExpression* lengthExpression ) {
	print( lengthExpression->GetName());
}

void CPrinter::Visit( const CNewExpression* newExpression ) {
	print( newExpression->GetName());
}

void CPrinter::Visit( const CNotExpression* notExpression ) {
	print( notExpression->GetName());
}

void CPrinter::Visit( const CPrintStatement* printStatement ) {
	print( printStatement->GetName());
}

void CPrinter::Visit( const CStatementList* statementList ) {
	print( statementList->GetName());
}

void CPrinter::Visit( const CVarDeclaration* varDeclaration ) {
	print( varDeclaration->GetName());
}

void CPrinter::Visit( const CVarDeclarationList* varDeclarationList ) {
	print( varDeclarationList->GetName());
}

void CPrinter::Visit( const CWhileStatement* whileStatement ) {
	print( whileStatement->GetName());
}

void CPrinter::Visit( const CBracketStatement* bracketStatement ) {
	print( bracketStatement->GetName());
}

void CPrinter::Visit( const CAssignmentStatement* assignmentStatement ) {
	print( assignmentStatement->GetName());
}

void CPrinter::Visit( const CIntArrayAssignmentStatement* intArrayAssignmentStatement ) {
	print(intArrayAssignmentStatement->GetName());
}

void CPrinter::Visit( const CBracketExpression* bracketExpression ) {
	print(bracketExpression->GetName());
}

void CPrinter::Visit( const CMethodArgumentsList* methodArgumentsList ) {
	print(methodArgumentsList->GetName());
}

void CPrinter::Visit( const CMethodHeaderDeclaration* methodHeaderDeclaration ) {
	print(methodHeaderDeclaration->GetName());
}

void CPrinter::Visit( const CMethodBodyDeclaration* methodBodyDeclaration ) {
	print(methodBodyDeclaration->GetName());
}

void CPrinter::Visit( const CMethodDeclaration* methodDeclaration ) {
	print(methodDeclaration->GetName());
}

void CPrinter::Visit( const CMethodDeclarationList* methodDeclarationList ) {
	print(methodDeclarationList->GetName());
}

void CPrinter::Visit( const CClassDeclaration* classDeclaration ) {
	print(classDeclaration->GetName());
}

void CPrinter::Visit( const CMainClass* mainClass ) {
	print(mainClass->GetName());

	mainClass->ClassName->Accept(this);
	mainClass->ArgumentName->Accept(this);
	mainClass->MainFunctionStatement->Accept(this);
}

void CPrinter::Visit( const CClassDeclarationList* classDeclarationList ) {
	print(classDeclarationList->GetName());
}

void CPrinter::Visit( const CGoal* goal ) {
	print(goal->GetName());
	goal->MainClass->Accept(this);
	goal->ClassDeclarationList->Accept(this);
}
