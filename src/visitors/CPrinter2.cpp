//
// Created by Ава Катушка on 07.11.15.
//

#include "CPrinter2.hpp"

#include <iostream>
#include "../Utils/ConsolePrinter.hpp"

void CPrinter2::Visit( const CBasicType* basicType ) {
	ConsolePrinter::print( basicType->GetName());
}

void CPrinter2::Visit( const CBinaryExpression* binaryExpression ) {
	ConsolePrinter::print( binaryExpression->GetName());

	ConsolePrinter::printTab();
	binaryExpression->LeftExpr->Accept( this );
	ConsolePrinter::printTab();
	ConsolePrinter::print( binaryExpression->BinaryExpressionType );
	ConsolePrinter::printTab();
	binaryExpression->RightExpr->Accept( this );
}

void CPrinter2::Visit( const CClassType* classType ) {
	ConsolePrinter::print( classType->GetName());


	ConsolePrinter::printTab();
	classType->ClassName->Accept( this );
}

void CPrinter2::Visit( const CConstant* constant ) {
	ConsolePrinter::print( constant->GetName());

	ConsolePrinter::printTab();
	ConsolePrinter::print( constant->Type );
	ConsolePrinter::printTab();
	ConsolePrinter::print( constant->Value );
}

void CPrinter2::Visit( const CExpressionList* expressionList ) {
	ConsolePrinter::print( expressionList->GetName());

	ConsolePrinter::printTab();
	expressionList->Expression->Accept( this );
	if ( expressionList->ExpressionList ) {
		ConsolePrinter::printTab();
		expressionList->ExpressionList->Accept( this );
	}
}

void CPrinter2::Visit( const CIdentifier* identifier ) {
	ConsolePrinter::print( identifier->GetName());
	ConsolePrinter::print( identifier->Id );
}

void CPrinter2::Visit( const CIfStatement* ifStatement ) {
	ConsolePrinter::print( ifStatement->GetName());

	ConsolePrinter::printTab();
	ifStatement->Expression->Accept( this );
	ConsolePrinter::printTab();
	ifStatement->TrueStatement->Accept( this );
	ConsolePrinter::printTab();
	ifStatement->FalseStatement->Accept( this );
}

void CPrinter2::Visit( const CIntArrayNewExpression* intArrayNewExpression ) {
	ConsolePrinter::print( intArrayNewExpression->GetName());

	ConsolePrinter::printTab();
	intArrayNewExpression->Expression->Accept( this );
}

void CPrinter2::Visit( const CInvocation* invocation ) {
	ConsolePrinter::print( invocation->GetName());

	ConsolePrinter::printTab();
	invocation->Expression->Accept( this );
	ConsolePrinter::printTab();
	invocation->Identifier->Accept( this );
	if ( invocation->ExpressionList ) {
		ConsolePrinter::printTab();
		invocation->ExpressionList->Accept( this );
	}
}

void CPrinter2::Visit( const CLengthExpression* lengthExpression ) {
	ConsolePrinter::print( lengthExpression->GetName());

	ConsolePrinter::printTab();
	lengthExpression->Expression->Accept( this );
}

void CPrinter2::Visit( const CNewExpression* newExpression ) {
	ConsolePrinter::print( newExpression->GetName());

	ConsolePrinter::printTab();
	newExpression->Id->Accept( this );
}

void CPrinter2::Visit( const CNotExpression* notExpression ) {
	ConsolePrinter::print( notExpression->GetName());

	ConsolePrinter::printTab();
	notExpression->Expression->Accept( this );
}

void CPrinter2::Visit( const CPrintStatement* printStatement ) {
	ConsolePrinter::print( printStatement->GetName());

	ConsolePrinter::printTab();
	printStatement->Expression->Accept( this );
}

void CPrinter2::Visit( const CStatementList* statementList ) {
	ConsolePrinter::print( statementList->GetName());

	ConsolePrinter::printTab();
	statementList->Statement->Accept( this );
	if ( statementList->Next ) {
		ConsolePrinter::printTab();
		statementList->Next->Accept( this );
	}
}

void CPrinter2::Visit( const CVarDeclaration* varDeclaration ) {
	ConsolePrinter::print( varDeclaration->GetName());

	ConsolePrinter::printTab();
	varDeclaration->Type->Accept( this );
	ConsolePrinter::printTab();
	varDeclaration->Identifier->Accept( this );
}

void CPrinter2::Visit( const CVarDeclarationList* varDeclarationList ) {
	ConsolePrinter::print( varDeclarationList->GetName());

	ConsolePrinter::printTab();
	varDeclarationList->VarDeclaration->Accept( this );
	if ( varDeclarationList->Next ) {
		ConsolePrinter::printTab();
		varDeclarationList->Next->Accept( this );
	}
}

void CPrinter2::Visit( const CWhileStatement* whileStatement ) {
	ConsolePrinter::print( whileStatement->GetName());

	ConsolePrinter::printTab();
	whileStatement->Expression->Accept( this );
	ConsolePrinter::printTab();
	whileStatement->Statement->Accept( this );
}

void CPrinter2::Visit( const CBracketStatement* bracketStatement ) {
	ConsolePrinter::print( bracketStatement->GetName());

	ConsolePrinter::printTab();
	bracketStatement->Statement->Accept( this );
}

void CPrinter2::Visit( const CAssignmentStatement* assignmentStatement ) {
	ConsolePrinter::print( assignmentStatement->GetName());

	ConsolePrinter::printTab();
	assignmentStatement->Identifier->Accept( this );
	ConsolePrinter::printTab();
	assignmentStatement->Expression->Accept( this );
}

void CPrinter2::Visit( const CIntArrayAssignmentStatement* intArrayAssignmentStatement ) {
	ConsolePrinter::print( intArrayAssignmentStatement->GetName());

	ConsolePrinter::printTab();
	intArrayAssignmentStatement->Identifier->Accept( this );
	ConsolePrinter::printTab();
	intArrayAssignmentStatement->Index->Accept( this );
	ConsolePrinter::printTab();
	intArrayAssignmentStatement->Expression->Accept( this );
}

void CPrinter2::Visit( const CBracketExpression* bracketExpression ) {
	ConsolePrinter::print( bracketExpression->GetName());

	ConsolePrinter::printTab();
	bracketExpression->Expression->Accept( this );
}

void CPrinter2::Visit( const CMethodArgumentsList* methodArgumentsList ) {
	ConsolePrinter::print( methodArgumentsList->GetName());

	ConsolePrinter::printTab();
	methodArgumentsList->VarDeclaration->Accept( this );
	if ( methodArgumentsList->Next ) {
		ConsolePrinter::printTab();
		methodArgumentsList->Next->Accept( this );
	}
}

void CPrinter2::Visit( const CMethodHeaderDeclaration* methodHeaderDeclaration ) {
	ConsolePrinter::print( methodHeaderDeclaration->GetName());

	ConsolePrinter::printTab();
	methodHeaderDeclaration->ReturnType->Accept( this );
	ConsolePrinter::printTab();
	methodHeaderDeclaration->MethodName->Accept( this );
	ConsolePrinter::printTab();
	if ( methodHeaderDeclaration->MethodArgumentList ) {
		methodHeaderDeclaration->MethodArgumentList->Accept( this );
	}
}

void CPrinter2::Visit( const CMethodBodyDeclaration* methodBodyDeclaration ) {
	ConsolePrinter::print( methodBodyDeclaration->GetName());

	if ( methodBodyDeclaration->VarDeclarationList ) {
		methodBodyDeclaration->VarDeclarationList->Accept( this );
	}
	if ( methodBodyDeclaration->StatementList ) {
		methodBodyDeclaration->StatementList->Accept( this );
	}
	methodBodyDeclaration->ReturnExpression->Accept( this );
}

void CPrinter2::Visit( const CMethodDeclaration* methodDeclaration ) {
	ConsolePrinter::print( methodDeclaration->GetName());

	ConsolePrinter::printTab();
	methodDeclaration->MethodHeaderDeclaration->Accept( this );
	ConsolePrinter::printTab();
	methodDeclaration->MethodBodyDeclaration->Accept( this );

}

void CPrinter2::Visit( const CMethodDeclarationList* methodDeclarationList ) {
	ConsolePrinter::print( methodDeclarationList->GetName());

	ConsolePrinter::printTab();
	methodDeclarationList->MethodDeclaration->Accept( this );
	if ( methodDeclarationList->MethodDeclarationList ) {
		ConsolePrinter::printTab();
		methodDeclarationList->MethodDeclarationList->Accept( this );
	}
}

void CPrinter2::Visit( const CClassDeclaration* classDeclaration ) {
	ConsolePrinter::print( classDeclaration->GetName());

	ConsolePrinter::printTab();
	classDeclaration->ClassName->Accept( this );
	ConsolePrinter::printTab();
	classDeclaration->BaseClassName->Accept( this );
	if ( classDeclaration->VarDeclarationList ) {
		ConsolePrinter::printTab();
		classDeclaration->VarDeclarationList->Accept( this );
	}
	if ( classDeclaration->MethodDeclarationList ) {
		ConsolePrinter::printTab();
		classDeclaration->MethodDeclarationList->Accept( this );
	}
}

void CPrinter2::Visit( const CMainClass* mainClass ) {
	ConsolePrinter::print( mainClass->GetName());

	ConsolePrinter::printTab();
	mainClass->ClassName->Accept( this );
	ConsolePrinter::printTab();
	mainClass->ArgumentName->Accept( this );
	ConsolePrinter::printTab();
	mainClass->MainFunctionStatement->Accept( this );
}

void CPrinter2::Visit( const CClassDeclarationList* classDeclarationList ) {
	ConsolePrinter::print( classDeclarationList->GetName());

	ConsolePrinter::printTab();
	classDeclarationList->ClassDeclaration->Accept( this );
	if ( classDeclarationList->ClassDeclarationList ) {
		ConsolePrinter::printTab();
		classDeclarationList->ClassDeclarationList->Accept( this );
	}
}

void CPrinter2::Visit( const CGoal* goal ) {
	ConsolePrinter::print( goal->GetName());

	ConsolePrinter::printTab();
	goal->MainClass->Accept( this );
	if ( goal->ClassDeclarationList ) {
		ConsolePrinter::printTab();
		goal->ClassDeclarationList->Accept( this );
	}
}


