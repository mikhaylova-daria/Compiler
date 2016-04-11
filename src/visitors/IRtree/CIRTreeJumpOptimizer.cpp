//
// Created by nicolai on 11.04.16.
//

#include "CIRTreeJumpOptimizer.h"
#include "../../IR/tree/IRTree.hpp"

using namespace IRTree;

std::shared_ptr<StatementList> IRTree::CIRTreeJumpOptimizer::Optimize(const std::shared_ptr<StatementList> &list) {
    if(list == nullptr) {
        return nullptr;
    }
    CJumpStatement* cjump = dynamic_cast<CJumpStatement*> (list->getHead().get());
    if( cjump != nullptr) {
        if( list->getNext() != nullptr ) {
            LabelStatement* label = dynamic_cast<LabelStatement*>(list->getNext().get());
            if( label != nullptr ) {
                if( label->getLabel().get() == cjump->getIfFalse().get()) {
                    return std::make_shared<StatementList>(list->getHead(), Optimize(list->getNext()));
                } else if(label->getLabel().get() == cjump->getIfTrue().get()) {
                    StatementPtr nextJump = std::make_shared<CJumpStatement>(
                            reverse(cjump->getOp()),
                            cjump->getLeft(), cjump->getRight(),
                            cjump->getIfFalse(), cjump->getIfTrue());
                    return std::make_shared<StatementList>(nextJump, Optimize(list->getNext()));
                }
            }
        }
        LabelPtr nextLabel = std::make_shared<Temp::CLabel> (storage);
        StatementPtr nextCJump = std::make_shared<CJumpStatement>(
                cjump->getOp(),
                cjump->getLeft(), cjump->getRight(),
                cjump->getIfTrue(), nextLabel
        );
        StatementPtr nextJump = std::make_shared<JumpStatement>(
                std::vector<LabelPtr>({cjump->getIfFalse()}), std::make_shared<ConstExp>(0)
        );
        std::shared_ptr<StatementList> tail = std::make_shared<StatementList>(nextJump, Optimize(list->getNext()));
        tail = std::make_shared<StatementList>(std::make_shared<LabelStatement>(nextLabel), tail);
        return std::make_shared<StatementList>(nextCJump, tail);
    }
    return std::make_shared<StatementList>(list->getHead(), Optimize(list->getNext()));
}

IRTree::CJUMP IRTree::CIRTreeJumpOptimizer::reverse(IRTree::CJUMP op) {
    switch(op) {
        case J_EQ: return J_NE;
        case J_NE: return J_EQ;
        case J_UGE: return J_ULT;
        case J_ULT : return J_UGE;
        case J_ULE: return J_UGT;
        case J_UGT: return J_ULE;
        case J_LT : return J_GE;
        case J_GE : return J_LT;
        case J_GT : return J_LE;
        case J_LE : return J_GT;
        default: assert(false);
    }
    return J_EQ;
}
