//
// Created by nicolai on 12.04.16.
//

#include "CIRTreeCodeGenerator.h"

using namespace IRTree;
using namespace CodeGeneration;

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::MoveStatement *moveStatement) {
    CTempPtr source(new Temp::CTemp(storage));
    CTempPtr dest(new Temp::CTemp(storage));
    target = source;
    moveStatement->getSource()->Accept(this);
    target = dest;
    moveStatement->getDestination()->Accept(this);
    code.push_back(InstructionPtr(new MOVE(source, dest, {})));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::ExpressionStatement *expressionStatement) {
    target = CTempPtr(new Temp::CTemp(storage));
    expressionStatement->getExpression()->Accept(this);
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::JumpStatement *jumpStatement) {
    if( jumpStatement->getLabelList().size() == 1) {
        code.push_back(InstructionPtr(new OPER("jmp [0]", {}, {}, {jumpStatement->getLabelList()})));
        return;
    }
    CTempPtr left(new Temp::CTemp(storage));
    target = left;
    jumpStatement->getExpPtr()->Accept(this);
    std::vector<LabelPtr> labels;
    for( int i = 0; i < jumpStatement->getLabelList().size(); i++ ) {
        labels.push_back(LabelPtr(new Temp::CLabel(storage)));
    }
    std::string cmd = std::string() + "leal [0](,{0}," + std::to_string(Bytes) + ") {0}";
    code.emplace_back(new OPER(cmd, {left}, {}, labels));
    for( int i = 0; i < jumpStatement->getLabelList().size(); i++ ) {
        code.push_back(InstructionPtr(new OPER("jmp [0]", {}, {}, {jumpStatement->getLabelList()[i]})));
    }
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::CJumpStatement *cJumpStatement) {
    CTempPtr left(new Temp::CTemp(storage));
    CTempPtr right(new Temp::CTemp(storage));
    target = left;
    cJumpStatement->getLeft()->Accept(this);
    target = right;
    cJumpStatement->getRight()->Accept(this);
    code.emplace_back(new OPER("cmpl {1}, {0}", {left, right}));
    code.emplace_back(new OPER(toStr(cJumpStatement->getOp()) + " [0]", {}, {}, {cJumpStatement->getIfTrue()}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::SEQStatement *seqStatement) {
    assert(false);
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::StatementList *statementList) {
    statementList->getHead()->Accept(this);
    if( statementList->getNext() != nullptr) {
        statementList->getNext()->Accept(this);
    }
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::LabelStatement *labelStatement) {
    code.emplace_back(new LABEL(labelStatement->getLabel()));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::ConstExp *constExp) {
    std::string cmd = "movl $" + std::to_string(constExp->getValue()) + ", %{0}";
    code.emplace_back(new OPER(cmd, {target}, {target}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::PlatformConstExp *platformConstExp) {
    int val;
    switch (platformConstExp->GetConstType()) {
        case TPlatformConstType::PCT_POINTER_SIZE: { val = Bytes; break;}
        default: assert(false);
    }

    std::string cmd = "movl $" + std::to_string(val) + ", %{0}";
    code.emplace_back(new OPER(cmd, {target}, {target}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::NameExp *nameExp) {
    assert(false);
    /*
    std::string cmd = "movl $" + nameExp->getName() + ", %{0}";
    code.push_back(new OPER(cmd, {target}, {target}));
     */
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::TempExp *tempExp) {
    code.emplace_back(new MOVE(tempExp->getCTemp(), target, {target}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::BinopExp *binopExp) {
    CTempPtr tg = target;
    CTempPtr left(new Temp::CTemp(storage));
    CTempPtr right(new Temp::CTemp(storage));
    binopExp->getLeft()->Accept(this);
    target = left;
    binopExp->getRight()->Accept(this);
    target = right;
    switch (binopExp->getBinop()) {
        case BINOP::AND : {
            code.emplace_back(new MOVE(right, tg, {tg}));
            code.emplace_back(new OPER("andl %{0}, %{1}", {left, tg}));
            break;
        }
        case BINOP::EQ : {
            code.emplace_back(new MOVE(right, tg, {tg}));
            code.emplace_back(new OPER("xorl %{0}, %{1}", {left, tg}));
            break;
        }
        case BINOP::LT : {
            code.emplace_back(new OPER("cmpl %{1}, %{0}", {left, right}));
            code.emplace_back(new OPER("movl %eflags, %{0}", {tg}));
            // CF нулевой бит
            code.emplace_back(new OPER("andl $1, %{0}", {tg}));
            break;
        }
        case BINOP::MINUS: {
            code.emplace_back(new MOVE(left, tg, {tg}));
            code.emplace_back(new OPER("subl %{0}, %{1}", {right, tg}));
            break;
        }
        case BINOP::PLUS: {
            code.emplace_back(new MOVE(left, tg, {tg}));
            code.emplace_back(new OPER("addl %{0}, %{1}", {right, tg}));
            break;
        }
        case BINOP ::MUL: {
            code.emplace_back(new MOVE(left, tg, {tg}));
            CTempPtr eax(new Temp::CTemp(storage.Get("eax")));
            CTempPtr edx(new Temp::CTemp(storage.Get("edx")));
            code.emplace_back(new OPER("movl %{1}, %eax", {right, eax}));
            code.emplace_back(new OPER("mull %{0}", {tg, eax}, {eax, edx}));
            break;
        }
        default: assert(false);
    }
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::MemExp *memExp) {
    CTempPtr tg = target;
    CTempPtr addr(new Temp::CTemp(storage));
    target = addr;
    memExp->getExp()->Accept(this);
    code.emplace_back(new OPER("movl (%{0}), %{1}", {addr, tg}, {tg}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::ExpList *expList) {
    CTempPtr buf(new Temp::CTemp(storage));
    target = buf;
    expList->getHead()->Accept(this);
    code.emplace_back(new OPER("pushl {0}", {buf}));
    if( expList->getNext() != nullptr) {
        expList->getNext()->Accept(this);
    }
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::CallExp *callExp) {
    CTempPtr tg = target;
    CTempPtr addr( new Temp::CTemp(storage));
    target = addr;
    //callExp->getFunc()->Accept(this);
    NameExp* name = dynamic_cast<NameExp*>(callExp->getFunc().get());
    assert(name != nullptr);
    callExp->getArgs()->Accept(this);
    CTempPtr eax(new Temp::CTemp(storage.Get("eax")));
    code.emplace_back(new OPER("call " + name->getLabel()->GetName(), {}, {eax}));
    code.emplace_back(new OPER("movl %eax, %{0}", {tg}, {tg}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::ESEQExp *eseqExp) {
    assert(false);
}

CodeGeneration::CCode CIRTreeCodeGenerator::Generate(StatementPtr ptr) {
    code.clear();
    ptr->Accept(this);
    return std::move(code);
}


