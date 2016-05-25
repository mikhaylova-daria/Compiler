//
// Created by nicolai on 05.04.16.
//

#include "CIRTreeLin.h"
using namespace IRTree;

void CIRTreeLin::Visit(const MoveStatement *moveStatement) {
    isLastSEQ = false;
}

void CIRTreeLin::Visit(const ExpressionStatement *expressionStatement) {
    isLastSEQ = false;
}

void CIRTreeLin::Visit(const JumpStatement *jumpStatement) {
    isLastSEQ = false;
}

void CIRTreeLin::Visit(const CJumpStatement *cJumpStatement) {
    isLastSEQ = false;
}

void CIRTreeLin::Visit(const SEQStatement *seqStatement) {
    seqStatement->getRight()->Accept(this);
    if( !isLastSEQ ) {
        currStmList = std::make_shared<StatementList>(seqStatement->getRight(), currStmList);
    }
    seqStatement->getLeft()->Accept(this);
    if( !isLastSEQ ) {
        currStmList = std::make_shared<StatementList>(seqStatement->getLeft(), currStmList);
    }
    isLastSEQ = true;
}

void CIRTreeLin::Visit(const StatementList *statementList) {
    isLastSEQ = false;
}

void CIRTreeLin::Visit(const LabelStatement *labelStatement) {
    isLastSEQ = false;
}

void CIRTreeLin::Visit(const ConstExp *constExp) {
    assert(false);
}

void CIRTreeLin::Visit(const PlatformConstExp *platformConstExp) {
    assert(false);
}

void CIRTreeLin::Visit(const NameExp *nameExp) {
    assert(false);
}

void CIRTreeLin::Visit(const TempExp *tempExp) {
    assert(false);
}

void CIRTreeLin::Visit(const BinopExp *binopExp) {
    assert(false);
}

void CIRTreeLin::Visit(const MemExp *memExp) {
    assert(false);
}

void CIRTreeLin::Visit(const ExpList *expList) {
    assert(false);
}

void CIRTreeLin::Visit(const CallExp *callExp) {
    assert(false);
}

void CIRTreeLin::Visit(const ESEQExp *eseqExp) {
    assert(false);
}

std::shared_ptr<StatementList> CIRTreeLin::Linearize(StatementPtr statement) {
    currStmList = nullptr;
    isLastSEQ = false;
    statement->Accept(this);
    return currStmList;
}
