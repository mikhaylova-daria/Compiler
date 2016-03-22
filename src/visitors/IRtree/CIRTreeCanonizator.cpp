//
// Created by nicolai on 21.03.16.
//

#include "CIRTreeCanonizator.h"

using namespace IRTree;

void CIRTreeCanonizator::Visit(const MoveStatement *moveStatement) {
    moveStatement->getSource()->Accept(this);
    ExpPtr source = currentNode;
    moveStatement->getDestination()->Accept(this);
    ExpPtr destination = currentNode;
    StmExpList ordered = reorder(makeExpList(destination, source));

    destination = ordered.expList->getHead();
    source = ordered.expList->getNext()->getHead();
    currentNode = wrap(ordered.statement, StatementPtr(new MoveStatement(destination, source)));
}

void CIRTreeCanonizator::Visit(const ExpressionStatement *expressionStatement) {
    expressionStatement->getExpression()->Accept(this);
    ExpPtr exp = currentNode;
    ESEQExp* eseq = dynamic_cast<ESEQExp*>(exp.get());
    if( eseq == nullptr ) {
        currentNode = StatementPtr(new ExpressionStatement(exp));
    } else {
        StatementPtr stm(new ExpressionStatement(eseq->getExpression()));
        currentNode = StatementPtr(new SEQStatement(eseq->getStatement(), stm));
    }
}

void CIRTreeCanonizator::Visit(const JumpStatement *jumpStatement) {
    jumpStatement->getExpPtr()->Accept(this);
    ExpPtr exp = currentNode;
    ESEQExp* eseq = dynamic_cast<ESEQExp*>(exp.get());
    if( eseq == nullptr ) {
        currentNode = StatementPtr(new JumpStatement(jumpStatement->getLabelList(), exp));
    } else {
        StatementPtr stm(new JumpStatement(jumpStatement->getLabelList(), eseq->getExpression()));
        currentNode = StatementPtr(new SEQStatement(eseq->getStatement(), stm));
    }
}

void CIRTreeCanonizator::Visit(const CJumpStatement *cJumpStatement) {
    cJumpStatement->getLeft()->Accept(this);
    ExpPtr leftExp = currentNode;
    cJumpStatement->getRight()->Accept(this);
    ExpPtr rightExp = currentNode;

    StmExpList ordered = reorder(makeExpList(leftExp, rightExp));
    leftExp = ordered.expList->getHead();
    rightExp = ordered.expList->getNext()->getHead();

    StatementPtr newCJump(new CJumpStatement(cJumpStatement->getOp(),
                                             leftExp, rightExp,
                                             cJumpStatement->getIfTrue(),
                                             cJumpStatement->getIfFalse()));
    currentNode = wrap(ordered.statement, newCJump);
}

void CIRTreeCanonizator::Visit(const SEQStatement *seqStatement) {
    seqStatement->getLeft()->Accept(this);
    StatementPtr leftSt = currentNode;
    seqStatement->getRight()->Accept(this);
    StatementPtr rightSt = currentNode;
    currentNode = StatementPtr(new SEQStatement(leftSt, rightSt));
}

void CIRTreeCanonizator::Visit(const StatementList*) {
    assert(false);
}

void CIRTreeCanonizator::Visit(const LabelStatement *labelStatement) {
    currentNode = StatementPtr(new LabelStatement(*labelStatement));
}

void CIRTreeCanonizator::Visit(const ConstExp *constExp) {
    currentNode = ExpPtr(new ConstExp(constExp->getValue()));
}

void CIRTreeCanonizator::Visit(const PlatformConstExp *platformConstExp) {
    currentNode = ExpPtr(new PlatformConstExp(platformConstExp->GetConstType()));
}

void CIRTreeCanonizator::Visit(const NameExp *nameExp) {
    currentNode = ExpPtr(new NameExp(*nameExp));
}

void CIRTreeCanonizator::Visit(const TempExp *tempExp) {
    currentNode = ExpPtr(new TempExp(tempExp->getCTemp(), tempExp->GetShift()));
}

void CIRTreeCanonizator::Visit(const BinopExp *binopExp) {
    binopExp->getLeft()->Accept(this);
    ExpPtr leftExp = currentNode;
    binopExp->getRight()->Accept(this);
    ExpPtr rightExp = currentNode;

    StmExpList ordered = reorder(makeExpList(leftExp, rightExp));
    leftExp = ordered.expList->getHead();
    rightExp = ordered.expList->getNext()->getHead();

    currentNode = wrap(ordered.statement, ExpPtr(new BinopExp(binopExp->getBinop(), leftExp, rightExp)));
}

void CIRTreeCanonizator::Visit(const MemExp *memExp) {
    memExp->getExp()->Accept(this);
    ExpPtr exp = currentNode;

    StmExpList ordered = reorder(makeExpList(exp));
    exp = ordered.expList->getHead();

    currentNode = wrap(ordered.statement, ExpPtr(new MemExp(exp)));
}

void CIRTreeCanonizator::Visit(const ExpList *expList) {

    expList->getHead()->Accept(this);
    ExpPtr head = currentNode;
    ExpListPtr tail = nullptr;
    if( expList->getNext() != nullptr ) {
        expList->getNext()->Accept(this);
        tail = currentNode;
    }
    currentNode = ExpListPtr(new ExpList(head, tail));
}

void CIRTreeCanonizator::Visit(const CallExp *callExp) {
    if( callExp->getArgs() != nullptr ) {

        callExp->getArgs()->Accept(this);
        ExpListPtr expList = currentNode;
        StmExpList ordered = reorder(expList);

        ExpPtr newCall(new CallExp(callExp->getFunc(), ordered.expList));
        ExpPtr exp = wrap(ordered.statement, ExpPtr(new CMovedCallExp(newCall)));
        exp->Accept(this);
    }

    currentNode = ExpPtr(new CallExp(callExp->getFunc(), nullptr));
}

void CIRTreeCanonizator::Visit(const ESEQExp *eseqExp) {
    eseqExp->getStatement()->Accept(this);
    StatementPtr statement = currentNode;
    eseqExp->getExpression()->Accept(this);
    ExpPtr exp = currentNode;

    StmExpList ordered = reorder(makeExpList(exp));
    if( ordered.statement != nullptr ) {
        statement = StatementPtr(new SEQStatement(statement, ordered.statement));
    }
    currentNode = ExpPtr(new ESEQExp(statement, ordered.expList->getHead()));
}

void CIRTreeCanonizator::Visit(const CMovedCallExp *movedCallExp) {
    ExpPtr tempExp(new TempExp( CTempPtr(new Temp::CTemp(storage)), 0) );
    StatementPtr move(new MoveStatement(tempExp, movedCallExp->CallExp));
    //ExpPtr read(new TempExp())
    ExpPtr eseq(new ESEQExp(move, tempExp));
    currentNode = eseq;
}
