//
// Created by Ава Катушка on 01.12.15.
//

//#include <stringlist.h>
#include "CIRTreePrinter.hpp"
#include "../../IR/tree/Expressions.hpp"
#include "../../IR/tree/Statements.hpp"


void IRTree::CIRTreePrinter::Visit( const IRTree::MoveStatement* moveStatement ) {
	TreeWalker treeWalker(this);
	print(moveStatement->getName());
	moveStatement->getSource()->Accept(this);
	moveStatement->getDestination()->Accept(this);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ExpressionStatement* expressionStatement ) {
	TreeWalker treeWalker(this);
	print(expressionStatement->getName());
	expressionStatement->getExpression()->Accept(this);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::JumpStatement* jumpStatement ) {
	TreeWalker treeWalker(this);
	print(jumpStatement->getName());
	jumpStatement->getExpPtr()->Accept(this);
	for (auto label : jumpStatement->getLabelList()) {
		print(label->GetName());
	}
}

void IRTree::CIRTreePrinter::Visit( const IRTree::CJumpStatement* cJumpStatement ) {
	TreeWalker treeWalker(this);
	print(cJumpStatement->getName());
	print("if True: " + cJumpStatement->getIfTrue()->GetName());
	print("if False: " + cJumpStatement->getIfFalse()->GetName());
	print(cJumpStatement->getOp());
	cJumpStatement->getLeft()->Accept(this);
	cJumpStatement->getRight()->Accept(this);
}

void IRTree::CIRTreePrinter::Visit( const IRTree::SEQStatement* seqStatement ) {
	TreeWalker treeWalker(this);
	print(seqStatement->getName());
	seqStatement->getLeft()->Accept(this);
	seqStatement->getRight()->Accept(this);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::StatementList* statementList ) {
	TreeWalker treeWalker(this);
	print(statementList->getName());
	statementList->getHead()->Accept(this);
	if (statementList->getNext()) {
		statementList->getNext()->Accept(this);
	}

}

void IRTree::CIRTreePrinter::Visit( const IRTree::LabelStatement* labelStatement ) {
	TreeWalker treeWalker(this);
	print(labelStatement->getName());
	print(labelStatement->getLabel()->GetName());
}

void IRTree::CIRTreePrinter::Visit( const IRTree::ConstExp* constExp ) {
	TreeWalker treeWalker(this);
	print(constExp->getName());
	print("value: " + std::to_string(constExp->getValue()));
}

void IRTree::CIRTreePrinter::Visit( const IRTree::PlatformConstExp* platformConstExp ) {
	TreeWalker treeWalker(this);
	print(platformConstExp->getName());
}

void IRTree::CIRTreePrinter::Visit( const IRTree::NameExp* nameExp ) {
	TreeWalker treeWalker(this);
	print(nameExp->getName());
	print(nameExp->getLabel()->GetName());
}

void IRTree::CIRTreePrinter::Visit( const IRTree::TempExp* tempExp ) {
	TreeWalker treeWalker(this);
	print(tempExp->getName() + ' ' + tempExp->getCTemp()->GetName() + " + " + std::to_string(tempExp->GetShift()));
}

void IRTree::CIRTreePrinter::Visit( const IRTree::BinopExp* binopExp ) {
	TreeWalker treeWalker(this);
	print(binopExp->getName());
	print(binopExp->getBinop());
	binopExp->getLeft()->Accept(this);
	binopExp->getRight()->Accept(this);
}

void IRTree::CIRTreePrinter::Visit( const IRTree::MemExp* memExp ) {
	TreeWalker treeWalker(this);
	print(memExp->getName());
    memExp->getExp()->Accept(this);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ExpList* expList ) {
	TreeWalker treeWalker(this);
	print(expList->getName());
	if (expList->getHead()) {
		expList->getHead()->Accept( this );
	}
	if (expList->getNext() != nullptr) {
		expList->getNext()->Accept(this);
	}
}

void IRTree::CIRTreePrinter::Visit( const IRTree::CallExp* callExp ) {
	TreeWalker treeWalker(this);
	print(callExp->getName());
	if (callExp->getArgs()) {
		callExp->getArgs()->Accept(this);
	}
	callExp->getFunc()->Accept(this);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ESEQExp* eseqExp ) {
	TreeWalker treeWalker(this);
	print(eseqExp->getName());
	eseqExp->getExpression()->Accept(this);
	eseqExp->getStatement()->Accept(this);

}
