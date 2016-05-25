//
// Created by nicolai on 12.04.16.
//

#include "CIRTreeCodeGenerator.h"

using namespace IRTree;
using namespace CodeGeneration;

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::MoveStatement *moveStatement) {
    CTempPtr source;
    auto sourceTemp = std::dynamic_pointer_cast<IRTree::TempExp>(moveStatement->getSource());
    CTempPtr dest;
    auto destTemp = std::dynamic_pointer_cast<IRTree::TempExp>(moveStatement->getDestination());
    if( sourceTemp == nullptr ) {
        source = CTempPtr(new Temp::CTemp(storage));
        target = source;
        moveStatement->getSource()->Accept(this);
    } else {
        source = sourceTemp->getCTemp();
    }
    if( destTemp == nullptr ) {
        dest = CTempPtr(new Temp::CTemp(storage));
        target = dest;
        moveStatement->getDestination()->Accept(this);
    } else {
        dest = destTemp->getCTemp();
    }
    code.push_back(InstructionPtr(new MOVE(source, dest)));
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

    CTempPtr source;
    auto sourceTemp = std::dynamic_pointer_cast<IRTree::TempExp>(jumpStatement->getExpPtr());
    if( sourceTemp == nullptr ) {
        source = CTempPtr(new Temp::CTemp(storage));
        target = source;
        jumpStatement->getExpPtr()->Accept(this);
    } else {
        source = sourceTemp->getCTemp();
    }

    std::vector<LabelPtr> labels;
    for( int i = 0; i < jumpStatement->getLabelList().size(); i++ ) {
        labels.push_back(LabelPtr(new Temp::CLabel(storage)));
    }
    std::string cmd = std::string() + "leaq [0](,{0}," + std::to_string(Bytes) + ") {0}";
    code.emplace_back(new OPER(cmd, {source}, {}, labels));
    for( int i = 0; i < jumpStatement->getLabelList().size(); i++ ) {
        code.push_back(InstructionPtr(new OPER("jmp [0]", {}, {}, {jumpStatement->getLabelList()[i]})));
    }
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::CJumpStatement *cJumpStatement) {
//    CTempPtr left(new Temp::CTemp(storage));
//    CTempPtr right(new Temp::CTemp(storage));
//    target = left;
//    cJumpStatement->getLeft()->Accept(this);
//    target = right;
//    cJumpStatement->getRight()->Accept(this);

    CTempPtr left;
    auto leftTemp = std::dynamic_pointer_cast<IRTree::TempExp>(cJumpStatement->getLeft());
    CTempPtr right;
    auto rightTemp = std::dynamic_pointer_cast<IRTree::TempExp>(cJumpStatement->getRight());
    if( leftTemp == nullptr ) {
        left = CTempPtr(new Temp::CTemp(storage));
        target = left;
        cJumpStatement->getLeft()->Accept(this);
    } else {
        left = leftTemp->getCTemp();
    }
    if( rightTemp == nullptr ) {
        right = CTempPtr(new Temp::CTemp(storage));
        target = right;
        cJumpStatement->getRight()->Accept(this);
    } else {
        right = rightTemp->getCTemp();
    }

    code.emplace_back(new OPER("cmpq %{1}, %{0}", {left, right}));
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
    std::string cmd = "movq $" + std::to_string(constExp->getValue()) + ", %{0}";
    code.emplace_back(new OPER(cmd, {target}, {target}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::PlatformConstExp *platformConstExp) {
    int val;
    switch (platformConstExp->GetConstType()) {
        case TPlatformConstType::PCT_POINTER_SIZE: { val = Bytes; break;}
        default: assert(false);
    }

    std::string cmd = "movq $" + std::to_string(val) + ", %{0}";
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
    code.emplace_back(new MOVE(tempExp->getCTemp(), target));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::BinopExp *binopExp) {
    CTempPtr tg = target;

    CTempPtr left;
    auto leftTemp = std::dynamic_pointer_cast<IRTree::TempExp>(binopExp->getLeft());
    CTempPtr right;
    auto rightTemp = std::dynamic_pointer_cast<IRTree::TempExp>(binopExp->getRight());
    if( leftTemp == nullptr ) {
        left = CTempPtr(new Temp::CTemp(storage));
        target = left;
        binopExp->getLeft()->Accept(this);
    } else {
        left = leftTemp->getCTemp();
    }
    if( rightTemp == nullptr ) {
        right = CTempPtr(new Temp::CTemp(storage));
        target = right;
        binopExp->getRight()->Accept(this);
    } else {
        right = rightTemp->getCTemp();
    }
//
//    CTempPtr left(new Temp::CTemp(storage));
//    CTempPtr right(new Temp::CTemp(storage));
//    binopExp->getLeft()->Accept(this);
//    target = left;
//    binopExp->getRight()->Accept(this);
//    target = right;
    switch (binopExp->getBinop()) {
        case BINOP::AND : {
            code.emplace_back(new MOVE(right, tg));
            code.emplace_back(new OPER("andq %{0}, %{1}", {left, tg}, {tg}));
            break;
        }
        case BINOP::EQ : {
            code.emplace_back(new MOVE(right, tg));
            code.emplace_back(new OPER("xorq %{0}, %{1}", {left, tg}, {tg}));
            break;
        }
        case BINOP::LT : {
            code.emplace_back(new OPER("cmpq %{1}, %{0}", {left, right}));
            code.emplace_back(new OPER("movq %rflags, %<0>", {}, {tg}));
            // CF нулевой бит
            code.emplace_back(new OPER("andq $1, %{0}", {tg}, {tg}));
            break;
        }
        case BINOP::MINUS: {
            code.emplace_back(new MOVE(left, tg));
            code.emplace_back(new OPER("subq %{0}, %{1}", {right, tg}, {tg}));
            break;
        }
        case BINOP::PLUS: {
            code.emplace_back(new MOVE(left, tg));
            code.emplace_back(new OPER("addq %{0}, %{1}", {right, tg}, {tg}));
            break;
        }
        case BINOP ::MUL: {
            //code.emplace_back(new MOVE(left, tg));
            CTempPtr eax(new Temp::CTemp(storage.Get("rax")));
            CTempPtr edx(new Temp::CTemp(storage.Get("rdx")));
            code.emplace_back(new OPER("movq %{0}, %rax", {right}, {eax}));
            code.emplace_back(new OPER("mulq %{0}", {left, eax}, {eax, edx}));
            code.emplace_back(new OPER("movq %rax, %<0>", {eax}, {tg}));
            break;
        }
        default: assert(false);
    }
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::MemExp *memExp) {
    CTempPtr tg = target;

    CTempPtr source;
    auto sourceTemp = std::dynamic_pointer_cast<IRTree::TempExp>(memExp->getExp());
    if( sourceTemp == nullptr ) {
        source = CTempPtr(new Temp::CTemp(storage));
        target = source;
        memExp->getExp()->Accept(this);
    } else {
        source = sourceTemp->getCTemp();
    }

    //CTempPtr addr(new Temp::CTemp(storage));
    //target = addr;
    memExp->getExp()->Accept(this);
    code.emplace_back(new OPER("movq (%{0}), %{1}", {source, tg}, {tg}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::ExpList *expList) {
    CTempPtr buf(new Temp::CTemp(storage));
    target = buf;
    expList->getHead()->Accept(this);
    code.emplace_back(new OPER("pushq %{0}", {buf}));
    if( expList->getNext() != nullptr) {
        expList->getNext()->Accept(this);
    }
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::CallExp *callExp) {
    CTempPtr tg = target;

    //callExp->getFunc()->Accept(this);
    NameExp* name = dynamic_cast<NameExp*>(callExp->getFunc().get());
    assert(name != nullptr);
    CTempPtr eax(new Temp::CTemp(storage.Get("rax")));
    code.emplace_back(new OPER("// ------ prepare call args -------", {}));

//    auto obj = std::dynamic_pointer_cast<IRTree::TempExp>(callExp->getArgs());
//    CTempPtr buf;
//    if(obj == nullptr) {
//        buf = CTempPtr(new Temp::CTemp(storage));
//        target = buf;
//        callExp->getArgs()->Accept(this);
//    } else {
//        buf = obj->getCTemp();
//    }
//    code.emplace_back(new OPER("pushq %{0}", {buf}));
    callExp->getArgs()->Accept(this);

    code.emplace_back(new OPER("call " + name->getLabel()->GetName(), {}, {eax}));
    code.emplace_back(new OPER("movq %rax, %<0>", {eax}, {tg}));
}

void IRTree::CIRTreeCodeGenerator::Visit(const IRTree::ESEQExp *eseqExp) {
    assert(false);
}

CodeGeneration::CCode CIRTreeCodeGenerator::Generate(StatementPtr ptr, const std::vector<Temp::CTempPtr>& args) {
    code.clear();
    code.emplace_back(new OPER("// define args operator", {}, args));
    isStartLabel = true;
    argsOnStack = &args;
    ptr->Accept(this);
    return std::move(code);
}


