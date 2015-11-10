#include "CPrettyPrinter.hpp"

void CPrettyPrinter::Visit( const CBinaryExpression* binaryExpression ) {
	binaryExpression->LeftExpr->Accept( this );
	switch( binaryExpression->BinaryExpressionType ) {
		case BE_PLUS : {
			std::cout << " + ";
			break;
		}
		case BE_MINUS : {
			std::cout << " - ";
			break;
		}
		case BE_MULTIPLICATION: {
			std::cout << " * ";
			break;
		}
		case BE_LESS: {
			std::cout << " < ";
			break;
		}
		case BE_AND: {
			std::cout << " && ";
			break;
		}
		case BE_EQUAL: {
			std::cout << " == ";
			break;
		}
		case BE_SQ_BRACKETS: {
			std::cout << "[ ";
			binaryExpression->RightExpr->Accept( this );
			std::cout << " ]";
			return;
		}
		default: {
			std::cout << " BE_UNRECOGNISED ";
			break;
		}
	}

	binaryExpression->RightExpr->Accept( this );
}

void CPrettyPrinter::Visit( const CType* type ) {
	std::cout << type->Name->GetName();
}

void CPrettyPrinter::Visit( const CVariable* variable ) {
    variable->Identifier->Accept( this );
}

void CPrettyPrinter::Visit( const CConstant* constant ) {
	std::cout << constant->Value;
}

void CPrettyPrinter::Visit( const CExpressionList* expressionList ) {

	expressionList->Expression->Accept( this );
	if ( expressionList->ExpressionList ) {
		std::cout << ", ";
		expressionList->ExpressionList->Accept( this );
	}
}

void CPrettyPrinter::Visit( const CIdentifier* identifier ) {
	std::cout << identifier->Symbol->GetName();
}

void CPrettyPrinter::Visit( const CIfStatement* ifStatement ) {
	std::cout << "if ( ";
	ifStatement->Expression->Accept( this );
	std::cout << ") ";
	ifStatement->TrueStatement->Accept( this );
	printTabs();
	std::cout << "else ";
	ifStatement->FalseStatement->Accept( this );
}

void CPrettyPrinter::Visit( const CIntArrayNewExpression* intArrayNewExpression ) {
	std::cout << " new int[";
	intArrayNewExpression->Expression->Accept( this );
	std::cout << "]";
}

void CPrettyPrinter::Visit( const CInvocation* invocation ) {

	invocation->Expression->Accept( this );
	std::cout << ".";
	invocation->Identifier->Accept( this );
	std::cout <<"( ";
	if ( invocation->ExpressionList ) {
		invocation->ExpressionList->Accept( this );
		std::cout << " ";
	}
	std::cout << ")";
}

void CPrettyPrinter::Visit( const CLengthExpression* lengthExpression ) {
	std::cout << ".length( ";
	lengthExpression->Expression->Accept( this );
	std::cout << " )";
}

void CPrettyPrinter::Visit( const CNewExpression* newExpression ) {
    //++treeDeep;
	//print( newExpression->GetName());
	std::cout<< "new ";
	
	newExpression->Id->Accept( this );
	std::cout << "( )";

}

void CPrettyPrinter::Visit( const CNotExpression* notExpression ) {
    //++treeDeep;
	//print( notExpression->GetName());

	std::cout<<"!";
	notExpression->Expression->Accept( this );
    //
}

void CPrettyPrinter::Visit( const CPrintStatement* printStatement ) {
    //++treeDeep;
	//print( printStatement->GetName());

	std::cout<< "System.out.println( ";
	printStatement->Expression->Accept( this );
	std::cout<< " );\n";
    //
}

void CPrettyPrinter::Visit( const CStatementList* statementList ) {
   
	//print( statementList->GetName());
	printTabs();
	statementList->Statement->Accept( this );
	if ( statementList->StatementList ) {
		statementList->StatementList->Accept( this );
	}
    
}

void CPrettyPrinter::Visit( const CVarDeclaration* varDeclaration ) {
   
	varDeclaration->Type->Accept( this );
	std::cout << " ";
	varDeclaration->Identifier->Accept( this );
    
}

void CPrettyPrinter::Visit( const CVarDeclarationList* varDeclarationList ) {


	printTabs();
	varDeclarationList->VarDeclaration->Accept( this );
	std::cout << ";\n";
	if ( varDeclarationList->Next ) {
		varDeclarationList->Next->Accept( this );
	}
    
}

void CPrettyPrinter::Visit( const CWhileStatement* whileStatement ) {
   
	std::cout << "while ( ";
	whileStatement->Expression->Accept( this );
	std::cout<< " ) ";
	whileStatement->Statement->Accept( this );
    
}

void CPrettyPrinter::Visit( const CBracketStatement* bracketStatement ) {

	std::cout << "{\n";
	++treeDeep;
	bracketStatement->StatementList->Accept( this );
	--treeDeep;
	printTabs();
	std::cout << "}\n";
    
}

void CPrettyPrinter::Visit( const CAssignmentStatement* assignmentStatement ) {
   
	//print( assignmentStatement->GetName());

	assignmentStatement->Variable->Accept( this );
	std::cout << " = ";
	assignmentStatement->Expression->Accept( this );
	std::cout<<";\n";
    
}
void CPrettyPrinter::Visit( const CIntArrayAssignmentStatement* intArrayAssignmentStatement ) {
   
	//print( intArrayAssignmentStatement->GetName());


	intArrayAssignmentStatement->Variable->Accept( this );

	std::cout << "[";

	intArrayAssignmentStatement->Index->Accept( this );
	std::cout << "] = ";
	
	intArrayAssignmentStatement->Expression->Accept( this );
	std::cout<<";\n";
    
}

void CPrettyPrinter::Visit( const CBracketExpression* bracketExpression ) {
	std::cout << "(";
	bracketExpression->Expression->Accept( this );
	std::cout << ")";
}

void CPrettyPrinter::Visit( const CMethodArgumentsList* methodArgumentsList ) {
	methodArgumentsList->VarDeclaration->Accept( this );
	if ( methodArgumentsList->Next ) {
		std::cout << ", ";
		methodArgumentsList->Next->Accept( this );
	}

}

void CPrettyPrinter::Visit( const CMethodHeaderDeclaration* methodHeaderDeclaration ) {
	printTabs();
	std::cout << "public ";
	methodHeaderDeclaration->ReturnType->Accept( this );
	std::cout << " ";
	methodHeaderDeclaration->MethodName->Accept( this );

	std::cout << "( ";
	if ( methodHeaderDeclaration->MethodArgumentList ) {
		methodHeaderDeclaration->MethodArgumentList->Accept( this );
	}
	std::cout << " ) {\n";
	++treeDeep;
    
}

void CPrettyPrinter::Visit( const CMethodBodyDeclaration* methodBodyDeclaration ) {
   

	if ( methodBodyDeclaration->VarDeclarationList ) {
		methodBodyDeclaration->VarDeclarationList->Accept( this );
	}
	if ( methodBodyDeclaration->StatementList ) {
		methodBodyDeclaration->StatementList->Accept( this );
	}
	printTabs();
	std::cout << "return ";
	methodBodyDeclaration->ReturnExpression->Accept( this );
	std::cout << ";\n";
	--treeDeep;
	printTabs();
	std::cout << "}\n";
	std::cout << "\n";
    
}

void CPrettyPrinter::Visit( const CMethodDeclaration* methodDeclaration ) {
   
	std::cout << "\n";
	methodDeclaration->MethodHeaderDeclaration->Accept( this );
	
	methodDeclaration->MethodBodyDeclaration->Accept( this );
    
}

void CPrettyPrinter::Visit( const CMethodDeclarationList* methodDeclarationList ) {
   

	
	methodDeclarationList->MethodDeclaration->Accept( this );
	if ( methodDeclarationList->MethodDeclarationList ) {
		
		methodDeclarationList->MethodDeclarationList->Accept( this );
	}
    
}

void CPrettyPrinter::Visit( const CClassDeclaration* classDeclaration ) {
	std::cout << "\n\n";
	printTabs();
	std::cout << "class ";
	classDeclaration->ClassName->Accept( this );
    if (classDeclaration->BaseClassName) {
		std::cout << " expends ";
        classDeclaration->BaseClassName->Accept(this);
    }
	std::cout << " {\n\n";
	++treeDeep;
	if ( classDeclaration->VarDeclarationList ) {
		classDeclaration->VarDeclarationList->Accept( this );
	}
	if ( classDeclaration->MethodDeclarationList ) {
		printTabs();
		classDeclaration->MethodDeclarationList->Accept( this );
	}
	--treeDeep;
	printTabs();
	std::cout << "}\n";
    
}

void CPrettyPrinter::Visit( const CMainClass* mainClass ) {
	std::cout << "class ";
	mainClass->ClassName->Accept( this );
	std::cout << " {\n";
	++treeDeep;
	std::cout << "\n";
	printTabs();
	std::cout << "public static void main( String[] ";
	mainClass->ArgumentName->Accept( this );
	std::cout << " ) {\n";
	++treeDeep;
	printTabs();
	mainClass->MainFunctionStatement->Accept( this );
	--treeDeep;
	printTabs();
	std::cout << "}\n";
	--treeDeep;
	printTabs();
	std::cout << "\n}\n";
    
}

void CPrettyPrinter::Visit( const CClassDeclarationList* classDeclarationList ) {
	printTabs();
	classDeclarationList->ClassDeclaration->Accept( this );
	if ( classDeclarationList->ClassDeclarationList ) {
		classDeclarationList->ClassDeclarationList->Accept( this );
	}

}

void CPrettyPrinter::Visit( const CGoal* goal ) {

	goal->MainClass->Accept( this );
	if ( goal->ClassDeclarationList ) {
		
		goal->ClassDeclarationList->Accept( this );
	}
}


