//
// Created by nicolai on 05.04.16.
//

#include "CIRTreeLinearizator.h"
using namespace IRTree;

void CIRTreeLinearizatior::Visit(const MoveStatement *moveStatement) {
    isLastSEQ = false;
}

void CIRTreeLinearizatior::Visit(const ExpressionStatement *expressionStatement) {
    isLastSEQ = false;
}

void CIRTreeLinearizatior::Visit(const JumpStatement *jumpStatement) {
    isLastSEQ = false;
}

void CIRTreeLinearizatior::Visit(const CJumpStatement *cJumpStatement) {
    isLastSEQ = false;
}

void CIRTreeLinearizatior::Visit(const SEQStatement *seqStatement) {
    if(collectStmList) {
        seqStatement->getRight()->Accept(this);
        if( isLastSEQ ) {
            currStmList = std::shared_ptr<StatementList>(new StatementList(seqStatement->getLeft(), currStmList));
        } else {
            currStmList = std::shared_ptr<StatementList>(new StatementList(
                    seqStatement->getLeft(),
                    std::shared_ptr<StatementList>(new StatementList(seqStatement->getRight(), nullptr))
            ));
        }
    } else {
        seqStatement->getRight()->Accept(this);
        StatementPtr right = isLastSEQ ? currSEQ : seqStatement->getRight();
        std::shared_ptr<SEQStatement> last = lastSEQ;
        seqStatement->getLeft()->Accept(this);
        StatementPtr left = isLastSEQ ? currSEQ : seqStatement->getLeft();
        if (isLastSEQ) {
            std::shared_ptr<SEQStatement> next(new SEQStatement(lastSEQ->getRight(), right));
            lastSEQ->setRight(next);
            lastSEQ = last == nullptr ? next : last;
        } else {
            currSEQ = std::shared_ptr<SEQStatement>(new SEQStatement(left, right));
            lastSEQ = last == nullptr ? currSEQ : last;
        }
    }
    isLastSEQ = true;
}

void CIRTreeLinearizatior::Visit(const StatementList *statementList) {
    isLastSEQ = false;
}

void CIRTreeLinearizatior::Visit(const LabelStatement *labelStatement) {
    isLastSEQ = false;
}

void CIRTreeLinearizatior::Visit(const ConstExp *constExp) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const PlatformConstExp *platformConstExp) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const NameExp *nameExp) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const TempExp *tempExp) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const BinopExp *binopExp) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const MemExp *memExp) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const ExpList *expList) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const CallExp *callExp) {
    assert(false);
}

void CIRTreeLinearizatior::Visit(const ESEQExp *eseqExp) {
    assert(false);
}

std::shared_ptr<StatementList> CIRTreeLinearizatior::Linearize(StatementPtr statement) {
    collectStmList = false;
    statement->Accept(this);
    collectStmList = true;
    currSEQ->Accept(this);
    return currStmList;
}
