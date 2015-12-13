//
// Created by nicolai on 17.11.15.
//

#ifndef MINIJAVACOMPILER_CIRTREEBUILDER_H
#define MINIJAVACOMPILER_CIRTREEBUILDER_H

#include "../tree/MinijavaTree.h"
#include "../IR/translate/translate.hpp"
#include "../IR/tree/IRTree.hpp"
#include "../frame/Frame.hpp"
#include "../frame/Temp.hpp"

using namespace SymbolTable;
using namespace Translate;
using namespace IRTree;
using namespace Temp;

class CIRTreeBuilder : public IVisitor {

public:


    CIRTreeBuilder(CStorage &storage, CTable &table) : storage(storage), table(table) { }

    virtual void Visit(const CConstant *constant);

    virtual void Visit(const CVariable *variable);

    virtual void Visit(const CType *type);

    virtual void Visit(const CBinaryExpression *binaryExpression);

    virtual void Visit(const CNotExpression *notExpression);

    virtual void Visit(const CLengthExpression *lengthExpression);

    virtual void Visit(const CExpressionList *expressionList);

    virtual void Visit(const CIdentifier *identifier);

    virtual void Visit(const CInvocation *invocation);

    virtual void Visit(const CNewExpression *newExpression);

    virtual void Visit(const CIntArrayNewExpression *intArrayNewExpression);

    virtual void Visit(const CStatementList *statementList);

    virtual void Visit(const CBracketStatement *bracketStatement);

    virtual void Visit(const CIfStatement *ifStatement);

    virtual void Visit(const CWhileStatement *whileStatement);

    virtual void Visit(const CPrintStatement *printStatement);

    virtual void Visit(const CAssignmentStatement *assignmentStatement);

    virtual void Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement);

    virtual void Visit(const CVarDeclaration *varDeclaration);

    virtual void Visit(const CVarDeclarationList *varDeclarationList);

    virtual void Visit(const CBracketExpression *bracketExpression);

    virtual void Visit(const CMethodArgumentsList *methodArgumentsList);

    virtual void Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration);

    virtual void Visit(const CMethodBodyDeclaration *methodBodyDeclaration);

    virtual void Visit(const CMethodDeclaration *methodDeclaration);

    virtual void Visit(const CMethodDeclarationList *methodDeclarationList);

    virtual void Visit(const CClassDeclaration *classDeclaration);

    virtual void Visit(const CMainClass *mainClass);

    virtual void Visit(const CClassDeclarationList *classDeclarationList);

    virtual void Visit(const CGoal *goal);

    struct Function {
        Function(const std::shared_ptr<ISubtreeWrapper> &root, const CSymbol *name) : root(root), name(name) { }

        std::shared_ptr<ISubtreeWrapper> root;
        const CSymbol* name;
    };
    std::vector<Function> functions;

private:
    CStorage& storage;
    CClassInfo currentClass;
    CMethodInfo currentMethod;
    CTypeInfo lastType;
    CTable& table;
    std::shared_ptr<ISubtreeWrapper> currNode;

    const CSymbol* genFunctionName(const CSymbol* className, const CSymbol* funcName) {
        return storage.Get(std::string("#") + className->GetName() + "." + funcName->GetName());
    }
    //
    //const CSymbol* genClassVarName(const CSymbol* name) {
    //    return storage.Get(std::string("#this_") + name->GetName());
    //}
    const std::string getNewFuncName() {
        return "#new";
    }
    const std::string getPrintFuncName() {
        return "#print";
    }
    const std::string getMainFuncName() {
        return "#main";
    }
    // В условных (void*)-ах
    ExpPtr buildZeroInitTree(ExpPtr allocationExpr, int size) {
        if (size == 0) {
            return allocationExpr;
        }
        assert(size > 0);
        ExpPtr addr(new TempExp(CTempPtr(new CTemp(storage)), 0));
        StatementPtr root(new MoveStatement(addr, allocationExpr));
        for (int i = 0; i < size; i++) {
            ExpPtr shift(new BinopExp(BINOP::MUL, ExpPtr(new ConstExp(i)),
                                      ExpPtr(new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE))));
            ExpPtr nextAddr(ExpPtr(new BinopExp(BINOP::PLUS, addr, shift)));
            root = StatementPtr(new SEQStatement(root, StatementPtr(new MoveStatement(nextAddr, ExpPtr(new ConstExp(0))))));
        }
        return ExpPtr(new ESEQExp(root, addr));
    }

    // В условных (void*)-ах
    ExpPtr buildZeroInitTree(ExpPtr allocationExpr, ExpPtr sizeExpr) {
        ExpPtr size(new TempExp(CTempPtr(new CTemp(storage)), 0));
        ExpPtr addr(new TempExp(CTempPtr(new CTemp(storage)), 0));
        StatementPtr root(new MoveStatement(addr, allocationExpr));
        root = StatementPtr(new SEQStatement(root, StatementPtr(new MoveStatement(size, sizeExpr))));
        /*
         * forLabel
         * jump expr trueLab falseLab
         * trueLab
         * move ...
         * jump forLabel
         * falseLab
         */
        LabelPtr trueLabel(new Temp::CLabel(storage));
        LabelPtr falseLabel(new Temp::CLabel(storage));
        LabelPtr forLabel(new Temp::CLabel(storage));
        ExpPtr zero(new ConstExp(0));
        ExpPtr one(new ConstExp(1));
        ExpPtr pointerSize(new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE));
        StatementPtr jumpForLabel(new JumpStatement({forLabel}, zero));
        StatementPtr jumpTrueFalseLabel(new CJumpStatement(CJUMP::J_EQ, size, zero, trueLabel, falseLabel));
        StatementPtr div(new MoveStatement(size, ExpPtr(new BinopExp(BINOP::DIV, size, one))));
        ExpPtr shift(new BinopExp(BINOP::MUL, size, pointerSize));
        ExpPtr nextAddr(new BinopExp(BINOP::PLUS, addr, shift));
        StatementPtr move(new MoveStatement(nextAddr, zero));

        root = StatementPtr(new SEQStatement(root, StatementPtr(new LabelStatement(forLabel))));
        root = StatementPtr(new SEQStatement(root, jumpTrueFalseLabel));
        root = StatementPtr(new SEQStatement(root, StatementPtr(new LabelStatement(trueLabel))));
        root = StatementPtr(new SEQStatement(root, div));
        root = StatementPtr(new SEQStatement(root, move));
        root = StatementPtr(new SEQStatement(root, jumpForLabel));
        root = StatementPtr(new SEQStatement(root, StatementPtr(new LabelStatement(falseLabel))));

        return ExpPtr(new ESEQExp(root, addr));
    }

    std::shared_ptr<ISubtreeWrapper> getNode(ExpPtr exp) {
        return std::shared_ptr<ISubtreeWrapper>(new CExpConverter(exp));
    }
    std::shared_ptr<ISubtreeWrapper> getNode(StatementPtr exp) {
        return std::shared_ptr<ISubtreeWrapper>(new CStatementConverter(exp));
    }
};


#endif //MINIJAVACOMPILER_CIRTREEBUILDER_H
