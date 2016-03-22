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
	defineName(moveStatement->getName(), moveStatement->id);
	printConnection(moveStatement->id, moveStatement->getSource()->id);
	printConnection(moveStatement->id, moveStatement->getDestination()->id);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ExpressionStatement* expressionStatement ) {
	TreeWalker treeWalker(this);
	print(expressionStatement->getName());
	expressionStatement->getExpression()->Accept(this);
	defineName(expressionStatement->getName(), expressionStatement->id);
	printConnection(expressionStatement->id, expressionStatement->getExpression()->id);
}

void IRTree::CIRTreePrinter::Visit( const IRTree::JumpStatement* jumpStatement ) {
	TreeWalker treeWalker(this);
	print(jumpStatement->getName());

	jumpStatement->getExpPtr()->Accept(this);
	printConnection(jumpStatement->id, jumpStatement->getExpPtr()->id);
	std::string labelString = "";
	for (auto label : jumpStatement->getLabelList()) {
		print(label->GetName());
		labelString += " " + label->GetName() ;

	}
	defineName(jumpStatement->getName() + "\n" + labelString, jumpStatement->id);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::CJumpStatement* cJumpStatement ) {
	TreeWalker treeWalker(this);
	print(cJumpStatement->getName());
	defineName(cJumpStatement->getName()
			   + "\nif True: " + cJumpStatement->getIfTrue()->GetName()
               + "\nif False: " + cJumpStatement->getIfFalse()->GetName()
               + "\noperation: " + CIRTreePrinter::strCJUMP(cJumpStatement->getOp())
			, cJumpStatement->id);
	print("if True: " + cJumpStatement->getIfTrue()->GetName());

	print("if False: " + cJumpStatement->getIfFalse()->GetName());
	print(cJumpStatement->getOp());

	cJumpStatement->getLeft()->Accept(this);
	printConnection(cJumpStatement->id, cJumpStatement->getLeft()->id);
	cJumpStatement->getRight()->Accept(this);
	printConnection(cJumpStatement->id, cJumpStatement->getRight()->id);
}

void IRTree::CIRTreePrinter::Visit( const IRTree::SEQStatement* seqStatement ) {
	TreeWalker treeWalker(this);
	print(seqStatement->getName());
	defineName(seqStatement->getName(), seqStatement->id);
	seqStatement->getLeft()->Accept(this);
	seqStatement->getRight()->Accept(this);
	printConnection(seqStatement->id, seqStatement->getLeft()->id);
	setColor(seqStatement->getLeft()->id, "lightblue");
	printConnection(seqStatement->id, seqStatement->getRight()->id);
	setColor(seqStatement->getRight()->id, "aquamarine");
}

void IRTree::CIRTreePrinter::Visit( const IRTree::StatementList* statementList ) {
	TreeWalker treeWalker(this);
	print(statementList->getName());
	defineName(statementList->getName(), statementList->id);
	statementList->getHead()->Accept(this);
	printConnection(statementList->id, statementList->getHead()->id);
	if (statementList->getNext()) {
		statementList->getNext()->Accept(this);
		printConnection(statementList->id, statementList->getNext()->id);
	}

}

void IRTree::CIRTreePrinter::Visit( const IRTree::LabelStatement* labelStatement ) {
	TreeWalker treeWalker(this);
	print(labelStatement->getName());
	defineName(labelStatement->getName() + "\n" + labelStatement->getLabel()->GetName(), labelStatement->id);
	print(labelStatement->getLabel()->GetName());
}

void IRTree::CIRTreePrinter::Visit( const IRTree::ConstExp* constExp ) {
	TreeWalker treeWalker(this);
	print(constExp->getName());
	defineName(constExp->getName() + "\nvalue: " + std::to_string(constExp->getValue()), constExp->id);
	setColor(constExp->id, "lemonchiffon");
	print("value: " + std::to_string(constExp->getValue()));
}

void IRTree::CIRTreePrinter::Visit( const IRTree::PlatformConstExp* platformConstExp ) {
	TreeWalker treeWalker(this);
	print(platformConstExp->getName());
	defineName(platformConstExp->getName(), platformConstExp->id);
}

void IRTree::CIRTreePrinter::Visit( const IRTree::NameExp* nameExp ) {
	TreeWalker treeWalker(this);
	print(nameExp->getName());
	defineName(nameExp->getName() + "\n" + nameExp->getLabel()->GetName(), nameExp->id);
	print(nameExp->getLabel()->GetName());
	setColor(nameExp->id, "thistle");
}

void IRTree::CIRTreePrinter::Visit( const IRTree::TempExp* tempExp ) {
	TreeWalker treeWalker(this);

	print(tempExp->getName() + ' ' + tempExp->getCTemp()->GetName() + " + " + std::to_string(tempExp->GetShift()));
	defineName(tempExp->getName() + ' ' + tempExp->getCTemp()->GetName() + " + " + std::to_string(tempExp->GetShift()), tempExp->id);
	setColor(tempExp->id, "darkseagreen");
}

void IRTree::CIRTreePrinter::Visit( const IRTree::BinopExp* binopExp ) {
	TreeWalker treeWalker(this);
	print(binopExp->getName());
	defineName(binopExp->getName() + "\n" + strBinop(binopExp->getBinop()), binopExp->id);
	setColor(binopExp->id, "lightpink");
	print(binopExp->getBinop());
	binopExp->getLeft()->Accept(this);
	binopExp->getRight()->Accept(this);
	printConnection(binopExp->id, binopExp->getLeft()->id);
	printConnection(binopExp->id, binopExp->getRight()->id);
}

void IRTree::CIRTreePrinter::Visit( const IRTree::MemExp* memExp ) {
	TreeWalker treeWalker(this);
	print(memExp->getName());
	defineName(memExp->getName(), memExp->id);
    memExp->getExp()->Accept(this);
	printConnection(memExp->id, memExp->getExp()->id);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ExpList* expList ) {
	TreeWalker treeWalker(this);
	print(expList->getName());
	defineName(expList->getName(), expList->id);
	if (expList->getHead()) {
		expList->getHead()->Accept( this );
		printConnection(expList->id, expList->getHead()->id);
	}
	if (expList->getNext() != nullptr) {
		expList->getNext()->Accept(this);
		printConnection(expList->id, expList->getNext()->id);
	}
}

void IRTree::CIRTreePrinter::Visit( const IRTree::CallExp* callExp ) {
	TreeWalker treeWalker(this);
	print(callExp->getName());
	defineName(callExp->getName(), callExp->id);
	if (callExp->getArgs()) {
		callExp->getArgs()->Accept(this);
		printConnection(callExp->id, callExp->getArgs()->id);
	}
	callExp->getFunc()->Accept(this);
	printConnection(callExp->id, callExp->getFunc()->id);

}

void IRTree::CIRTreePrinter::Visit( const IRTree::ESEQExp* eseqExp ) {
	TreeWalker treeWalker(this);
	print(eseqExp->getName());
	defineName(eseqExp->getName(), eseqExp->id);
	eseqExp->getExpression()->Accept(this);
	printConnection(eseqExp->id, eseqExp->getExpression()->id);
	eseqExp->getStatement()->Accept(this);
	printConnection(eseqExp->id, eseqExp->getStatement()->id);

}
