//
// Created by Ава Катушка on 07.11.15.
//

#include "CPrinter2.hpp"

void CPrinter2::Visit( const CBinaryExpression* binaryExpression ) {
    ++treeDeep;
	print( binaryExpression->GetName());
	binaryExpression->LeftExpr->Accept( this );
	print( binaryExpression->BinaryExpressionType );
	binaryExpression->RightExpr->Accept( this );


    --treeDeep;
}

void CPrinter2::Visit( const CType* type ) {
    ++treeDeep;
	print( type->GetName() );

    print( type->Name->GetName() );

	std::cout << type->Name->GetName() << " ";
    --treeDeep;
}

void CPrinter2::Visit( const CVariable* variable ) {
    ++treeDeep;

    print( variable->GetName() );
	std::cout << variable->Identifier->GetName()<<" ";
    variable->Identifier->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CConstant* constant ) {
    ++treeDeep;
	print( constant->GetName() + " " + constant->Type->Name->GetName() + "(" + constant->Value + ")");
    --treeDeep;
}

void CPrinter2::Visit( const CExpressionList* expressionList ) {
    ++treeDeep;
	print( expressionList->GetName());

	
	expressionList->Expression->Accept( this );
	if ( expressionList->ExpressionList ) {
		
		expressionList->ExpressionList->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CIdentifier* identifier ) {
    ++treeDeep;
	print( identifier->GetName() + "(" + identifier->Symbol->GetName() + ")");
    --treeDeep;
}

void CPrinter2::Visit( const CIfStatement* ifStatement ) {
    ++treeDeep;
	print( ifStatement->GetName());

	
	ifStatement->Expression->Accept( this );
	
	ifStatement->TrueStatement->Accept( this );
	
	ifStatement->FalseStatement->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CIntArrayNewExpression* intArrayNewExpression ) {
    ++treeDeep;
	print( intArrayNewExpression->GetName());

	
	intArrayNewExpression->Expression->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CInvocation* invocation ) {
    ++treeDeep;
	print( invocation->GetName());

	
	invocation->Expression->Accept( this );
	
	invocation->Identifier->Accept( this );
	if ( invocation->ExpressionList ) {
		
		invocation->ExpressionList->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CLengthExpression* lengthExpression ) {
    ++treeDeep;
	print( lengthExpression->GetName());

	
	lengthExpression->Expression->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CNewExpression* newExpression ) {
    ++treeDeep;
	print( newExpression->GetName());

	
	newExpression->Id->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CNotExpression* notExpression ) {
    ++treeDeep;
	print( notExpression->GetName());

	
	notExpression->Expression->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CPrintStatement* printStatement ) {
    ++treeDeep;
	print( printStatement->GetName());

	
	printStatement->Expression->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CStatementList* statementList ) {
    ++treeDeep;
	print( statementList->GetName());

	
	statementList->Statement->Accept( this );
	if ( statementList->Next ) {
		
		statementList->Next->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CVarDeclaration* varDeclaration ) {
    ++treeDeep;
	print( varDeclaration->GetName());
	printTabs();
	std::cout << varDeclaration->Type->Name->GetName() << " " << varDeclaration->Identifier->Symbol->GetName() <<";"<<std::endl;
	varDeclaration->Type->Accept( this );
	varDeclaration->Identifier->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CVarDeclarationList* varDeclarationList ) {
    ++treeDeep;
	print( varDeclarationList->GetName());

	
	varDeclarationList->VarDeclaration->Accept( this );
	if ( varDeclarationList->Next ) {
		
		varDeclarationList->Next->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CWhileStatement* whileStatement ) {
    ++treeDeep;
	print( whileStatement->GetName());

	
	whileStatement->Expression->Accept( this );
	
	whileStatement->Statement->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CBracketStatement* bracketStatement ) {
    ++treeDeep;
	print( bracketStatement->GetName());

	
	bracketStatement->Statement->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CAssignmentStatement* assignmentStatement ) {
    ++treeDeep;
	print( assignmentStatement->GetName());

	
	assignmentStatement->Identifier->Accept( this );
	
	assignmentStatement->Expression->Accept( this );
    --treeDeep;
}
void CPrinter2::Visit( const CIntArrayAssignmentStatement* intArrayAssignmentStatement ) {
    ++treeDeep;
	print( intArrayAssignmentStatement->GetName());

	
	intArrayAssignmentStatement->Identifier->Accept( this );
	
	intArrayAssignmentStatement->Index->Accept( this );
	
	intArrayAssignmentStatement->Expression->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CBracketExpression* bracketExpression ) {
    ++treeDeep;
	print( bracketExpression->GetName());

	
	bracketExpression->Expression->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CMethodArgumentsList* methodArgumentsList ) {
    ++treeDeep;
	print( methodArgumentsList->GetName());

	
	methodArgumentsList->VarDeclaration->Accept( this );
	if ( methodArgumentsList->Next ) {
		
		methodArgumentsList->Next->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CMethodHeaderDeclaration* methodHeaderDeclaration ) {
    ++treeDeep;
	print( methodHeaderDeclaration->GetName());

	
	methodHeaderDeclaration->ReturnType->Accept( this );
	
	methodHeaderDeclaration->MethodName->Accept( this );
	
	if ( methodHeaderDeclaration->MethodArgumentList ) {
		methodHeaderDeclaration->MethodArgumentList->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CMethodBodyDeclaration* methodBodyDeclaration ) {
    ++treeDeep;
	print( methodBodyDeclaration->GetName());

	if ( methodBodyDeclaration->VarDeclarationList ) {
		methodBodyDeclaration->VarDeclarationList->Accept( this );
	}
	if ( methodBodyDeclaration->StatementList ) {
		methodBodyDeclaration->StatementList->Accept( this );
	}
	methodBodyDeclaration->ReturnExpression->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CMethodDeclaration* methodDeclaration ) {
    ++treeDeep;
	print( methodDeclaration->GetName());

	
	methodDeclaration->MethodHeaderDeclaration->Accept( this );
	
	methodDeclaration->MethodBodyDeclaration->Accept( this );

    --treeDeep;
}

void CPrinter2::Visit( const CMethodDeclarationList* methodDeclarationList ) {
    ++treeDeep;
	print( methodDeclarationList->GetName());

	
	methodDeclarationList->MethodDeclaration->Accept( this );
	if ( methodDeclarationList->MethodDeclarationList ) {
		
		methodDeclarationList->MethodDeclarationList->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CClassDeclaration* classDeclaration ) {
    ++treeDeep;
	print( classDeclaration->GetName());

	
	classDeclaration->ClassName->Accept( this );

    if (classDeclaration->BaseClassName) {
        classDeclaration->BaseClassName->Accept(this);
    }
	if ( classDeclaration->VarDeclarationList ) {
		
		classDeclaration->VarDeclarationList->Accept( this );
	}
	if ( classDeclaration->MethodDeclarationList ) {
		
		classDeclaration->MethodDeclarationList->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CMainClass* mainClass ) {
    ++treeDeep;
	print( mainClass->GetName());

	std::cout << "class " << mainClass->ClassName->Symbol->GetName() << " {" << std::endl;
	std::cout << "\tpublic static void main( String[] " << mainClass->ArgumentName->Symbol->GetName() << " ) {" << std::endl;
	mainClass->ClassName->Accept( this );
	
	mainClass->ArgumentName->Accept( this );
	
	mainClass->MainFunctionStatement->Accept( this );
    --treeDeep;
}

void CPrinter2::Visit( const CClassDeclarationList* classDeclarationList ) {
    ++treeDeep;
	print( classDeclarationList->GetName());

	classDeclarationList->ClassDeclaration->Accept( this );
	if ( classDeclarationList->ClassDeclarationList ) {
		
		classDeclarationList->ClassDeclarationList->Accept( this );
	}
    --treeDeep;
}

void CPrinter2::Visit( const CGoal* goal ) {
	print( goal->GetName());

	goal->MainClass->Accept( this );
	if ( goal->ClassDeclarationList ) {
		
		goal->ClassDeclarationList->Accept( this );
	}
}


