//
// Created by Ава Катушка on 01.12.15.
//

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
		label->GetName();
	}
}

void IRTree::CIRTreePrinter::Visit( const IRTree::CJumpStatement* cJumpStatement ) {
	TreeWalker treeWalker(this);
	print(cJumpStatement->getName());
	cJumpStatement->

}

void IRTree::CIRTreePrinter::Visit( const IRTree::SEQStatement* seqStatement ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::StatementList* statementList ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::LabelStatement* labelStatement ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ConstExp* constExp ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::PlatformConstExp* platformConstExp ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::NameExp* nameExp ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::TempExp* tempExp ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::BinopExp* binopExp ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::MemExp* memExp ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ExpList* expList ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::CallExp* callExp ) {

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ESEQExp* eseqExp ) {

}
