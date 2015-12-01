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
        std::shared_ptr<ISubtreeWrapper> root;
        const CSymbol* name;
    };
    std::vector<Function> functions;
    std::shared_ptr<ISubtreeWrapper> currNode;

private:
    CStorage& storage;
    CClassInfo currentClass;
    CMethodInfo currentMethod;
    CTypeInfo lastType;
    CTable& table;

    const CSymbol* genFunctionName(const CSymbol* className, const CSymbol* funcName) {
        return storage.Get(std::string("#") + className->GetName() + "." + funcName->GetName());
    }
    const std::string getNewFuncName() {
        return "#new";
    }
    const std::string getPrintFuncName() {
        return "#print";
    }
    // В условных (void*)-ах
    ExpPtr buildZeroInitTree(ExpPtr allocationExpr, int size) {
        if (size == 0) {
            return allocationExpr;
        }
        assert(size > 0);
        CTempPtr addr = new CTemp(storage);
        StatementPtr root = new MoveStatement(new TempExp(addr), allocationExpr);
        for (int i = 0; i < size; i++) {
            ExpPtr shift = new BinopExp(BINOP::MUL, new ConstExp(i),
                                        new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE));
            ExpPtr nextAddr = new BinopExp(BINOP::PLUS, addr, shift);
            root = new SEQStatement(root, new MoveStatement(nextAddr, new ConstExp(0)));
        }
        return new ESEQExp(root, addr);
    }

    // В условных (void*)-ах
    ExpPtr buildZeroInitTree(ExpPtr allocationExpr, ExpPtr sizeExpr) {
        CTempPtr size = new CTemp(storage);
        CTempPtr addr = new CTemp(storage);
        StatementPtr root = new MoveStatement(new TempExp(addr), allocationExpr);
        root = new SEQStatement(root, new MoveStatement(new TempExp(size), sizeExpr));
        /*
         * forLabel
         * jump expr trueLab falseLab
         * trueLab
         * move ...
         * jump forLabel
         * falseLab
         */
        ExpPtr trueLabel = new Temp::CTemp(storage);
        ExpPtr falseLabel = new Temp::CTemp(storage);
        ExpPtr forLabel = new Temp::CTemp(storage);
        StatementPtr jumpForLabel = new JumpStatement({forLabel}, new ConstExp(0));
        StatementPtr jumpTrueFalseLabel = new CJumpStatement(CJUMP::EQ, size, new ConstExp(0), trueLabel, falseLabel);
        ExpPtr div = new BinopExp(BINOP::DIV, size, new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE));
        ExpPtr shift = new BinopExp(BINOP::MUL, size,
                                    new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE));
        ExpPtr nextAddr = new BinopExp(BINOP::PLUS, addr, shift);
        StatementPtr move = new MoveStatement(nextAddr, new ConstExp(0));

        root = new SEQStatement(root, forLabel);
        root = new SEQStatement(root, jumpTrueFalseLabel);
        root = new SEQStatement(root, trueLabel);
        root = new SEQStatement(root, div);
        root = new SEQStatement(root, move);
        root = new SEQStatement(root, jumpForLabel);
        root = new SEQStatement(root, falseLabel);

        return new ESEQExp(root, addr);
    }
};


#endif //MINIJAVACOMPILER_CIRTREEBUILDER_H
