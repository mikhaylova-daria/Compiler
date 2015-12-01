//
// Created by nicolai on 17.11.15.
//

#include "CIRTreeBuilder.h"
//#include "../frame/Frame.hpp"
#include <cmath>

void CIRTreeBuilder::Visit(const CConstant *constant) {
    currNode = new ConstExp(atoi(constant->Value));
    constant->Type->Accept(this);
}

// возвращает значение, записанное в переменной. а не адрес
void CIRTreeBuilder::Visit(const CVariable *variable) {
    variable->Identifier->Accept(this);
    CVarInfo varInfo = currentMethod.FindVarInfo(variable->Identifier->Symbol);
    if (varInfo.VarName == nullptr) {
        varInfo = table.FindVarInfo(currentClass.Name, variable->Identifier->Symbol);
        assert(varInfo.VarName != nullptr);
        //int shift = table.FindVarPosition(currentClass.Name, variable->Identifier->Symbol);
        currNode = new TempExp(new Temp::CTemp(genClassVarName(variable->Identifier->Symbol)));
    } else {
        // заворачиваем в Temp, т.к. значение может жить в памяти или в регистре
        currNode = new TempExp(new Temp::CTemp(variable->Identifier->Symbol));
    }
    assert(varInfo.VarName != nullptr);
    lastType = varInfo.TypeInfo;
}

void CIRTreeBuilder::Visit(const CType *type) {
    lastType = CTypeInfo(type->Name, type->Type);
}

// Принимает значения переменных, а не адреса
void CIRTreeBuilder::Visit(const CBinaryExpression *binaryExpression) {
    binaryExpression->LeftExpr->Accept(this);
    ExpPtr leftExpr = currNode;
    binaryExpression->RightExpr->Accept(this);
    ExpPtr rightExpr = currNode;

    static_assert(TBinaryExpression::BE_COUNT == 7, "TBinaryExpression switch failed");
    switch (binaryExpression->BinaryExpressionType) {
        case TBinaryExpression::BE_AND :
            currNode = new BinopExp(BINOP::AND, leftExpr, rightExpr);
            break;
        case TBinaryExpression::BE_EQUAL :
            currNode = new BinopExp(BINOP::EQ, leftExpr, rightExpr);
            break;
        case TBinaryExpression::BE_LESS :
            currNode = new BinopExp(BINOP::LT, leftExpr, rightExpr);
            break;
        case TBinaryExpression::BE_MINUS :
            currNode = new BinopExp(BINOP::MINUS, leftExpr, rightExpr);
            break;
        case TBinaryExpression::BE_MULTIPLICATION :
            currNode = new BinopExp(BINOP::MUL, leftExpr, rightExpr);
            break;
        case TBinaryExpression::BE_PLUS:
            currNode = new BinopExp(BINOP::PLUS, leftExpr, rightExpr);
            break;
        case TBinaryExpression::BE_SQ_BRACKETS : {
            // leftExpr - массив, в нем хранится адрес переменной
            ExpPtr sizeBinop = new BinopExp(BINOP::MUL,
                                            new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE),
                                            rightExpr);
            // приняли значение, значит leftExpr не нужно разыменовывать
            currNode = new MemExp(new BinopExp(BINOP::PLUS, leftExpr, sizeBinop));
            break;
        } default:
            assert(false);
    }
}

void CIRTreeBuilder::Visit(const CNotExpression *notExpression) {
    notExpression->Expression->Accept(this);
    // currNode - значение
    currNode = new BinopExp(BINOP::EQ, currNode, new ConstExp(0));
    assert(lastType.VarType == TType::T_BOOL);
}

void CIRTreeBuilder::Visit(const CLengthExpression *lengthExpression) {
    lengthExpression->Expression->Accept(this);
    assert(lastType.VarType == TType::T_INT_ARRAY);
    // размер лежит в currNode[-1]
    ExpPtr binop = new BinopExp(BINOP::MINUS, currNode, new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE));
    currNode = new MemExp(binop);
    lastType = CTypeInfo(storage.Get("int"), TType::T_INT);
}

void CIRTreeBuilder::Visit(const CExpressionList *expressionList) {
    expressionList->Expression->Accept(this);
    std::shared_ptr<ISubtreeWrapper> leftExpr = currNode;
    if (expressionList->ExpressionList != nullptr) {
        expressionList->ExpressionList->Accept(this);
        currNode = new ExpList(leftExpr, currNode);
    } else {
        currNode = new ExpList(leftExpr, nullptr);
    }
}

void CIRTreeBuilder::Visit(const CIdentifier *) {

}

void CIRTreeBuilder::Visit(const CInvocation *invocation) {
    if (invocation->ExpressionList != nullptr) {
        invocation->ExpressionList->Accept(this);
    }
    ExpListPtr callList = currNode;
    invocation->Identifier->Accept(this);
    invocation->Expression->Accept(this);
    assert(lastType.VarType == TType::T_CLASS);
    const CSymbol* methodBase = table.FindMethodBase(currentClass.Name, currentMethod.Name);
    assert(methodBase != nullptr);
    const CSymbol* funcName = genFunctionName(methodBase, currentMethod.Name);
    currNode = new CallExp(new NameExp(new CLabel(funcName)), callList);
    lastType = table.FindMethodInfo(currentClass.Name, currentMethod.Name).ReturnType;
    assert(lastType.TypeName != nullptr);
}

void CIRTreeBuilder::Visit(const CNewExpression *newExpression) {
    newExpression->Id->Accept(this);

    int size = table.FindClassSize(newExpression->Id->Symbol);
    assert(size != NOT_FOUND);
    currNode = new CallExp(new NameExp(new CLabel(storage.Get(getNewFuncName()))),
                           new ExpList(new ConstExp(size), nullptr));
    // инициализация
    currNode = buildZeroInitTree(currNode, size);
    auto classIterator = table.FindClass(newExpression->Id->Symbol);
    const CClassInfo& classInfo = *classIterator;
    lastType = CTypeInfo(classInfo.Name, TType::T_CLASS);
}

void CIRTreeBuilder::Visit(const CIntArrayNewExpression *intArrayNewExpression) {
    intArrayNewExpression->Expression->Accept(this);
    assert(lastType.VarType == TType::T_INT);
    ExpPtr size = currNode;
    currNode = new CallExp(new NameExp(new CLabel(storage.Get(getNewFuncName()))),
                           new ExpList(size, nullptr));
    // инициализация
    currNode = buildZeroInitTree(currNode, size);
    lastType = CTypeInfo(storage.Get("int[]"), TType::T_INT_ARRAY);
}

void CIRTreeBuilder::Visit(const CStatementList *statementList) {
    statementList->Statement->Accept(this);
    std::shared_ptr<ISubtreeWrapper> leftStm = currNode;

    if (statementList->StatementList != nullptr) {
        statementList->StatementList->Accept(this);
        currNode = new StatementList(leftStm, currNode);
    } else {
        currNode = new StatementList(leftStm, nullptr);
    }
}

void CIRTreeBuilder::Visit(const CBracketStatement *bracketStatement) {
    if (bracketStatement->StatementList != nullptr) {
        bracketStatement->StatementList->Accept(this);
    } else {
        currNode = nullptr;
    }
}

void CIRTreeBuilder::Visit(const CIfStatement *ifStatement) {
    ifStatement->Expression->Accept(this);
    assert(lastType.VarType == TType::T_BOOL);
    ExpPtr expPtr = currNode;
    ifStatement->TrueStatement->Accept(this);
    StatementPtr  trueStatement = currNode;
    ifStatement->FalseStatement->Accept(this);
    StatementPtr  falseStatement = currNode;
    ExpPtr trueLabel = new Temp::CTemp(storage);
    ExpPtr falseLabel = new Temp::CTemp(storage);
    ExpPtr finLabel = new Temp::CTemp(storage);
    StatementPtr jump = new CJumpStatement(CJUMP::EQ, expPtr, new ConstExp(0), trueLabel, falseLabel);
    /*
     * jump exp trueLab falseLab:
     *   trueLab
     *     trueSt
     *     jump fin
     *   falseLab
     *     falseSt
     *   finLab
     */
    currNode = new SEQStatement(falseStatement, finLabel);
    currNode = new SEQStatement(new LabelStatement(falseLabel), currNode);
    currNode = new SEQStatement(new JumpStatement({finLabel}, new ConstExp(0)), currNode);
    currNode = new SEQStatement(trueStatement, currNode);
    currNode = new SEQStatement(new LabelStatement(trueLabel), currNode);
    currNode = new SEQStatement(jump, currNode);
}

void CIRTreeBuilder::Visit(const CWhileStatement *whileStatement) {
    whileStatement->Expression->Accept(this);
    assert(lastType.VarType == TType::T_BOOL);
    ExpPtr exp = currNode;
    whileStatement->Statement->Accept(this);
    StatementPtr statementPtr = currNode;
    /*
     * whileLab
     * jump exp trueLab falseLab
     * trueLab
     * st
     * jump whileLab
     * falseLab
     */
    ExpPtr trueLabel = new Temp::CTemp(storage);
    ExpPtr falseLabel = new Temp::CTemp(storage);
    ExpPtr whileLabel = new Temp::CTemp(storage);
    StatementPtr jumpWhileLabel = new JumpStatement({whileLabel}, new ConstExp(0));
    StatementPtr jumpTrueFalseLabel = new CJumpStatement(CJUMP::EQ, exp, new ConstExp(0), trueLabel, falseLabel);
    currNode = new SEQStatement(jumpWhileLabel, falseLabel);
    currNode = new SEQStatement(statementPtr, currNode);
    currNode = new SEQStatement(trueLabel, currNode);
    currNode = new SEQStatement(jumpTrueFalseLabel, currNode);
    currNode = new SEQStatement(whileLabel, currNode);
}

void CIRTreeBuilder::Visit(const CPrintStatement *printStatement) {
    printStatement->Expression->Accept(this);
    assert (lastType.VarType == TType::T_INT);
    currNode = new CallExp(new NameExp(new CLabel(storage.Get(getPrintFuncName()))), new ExpList(currNode, nullptr));
}

void CIRTreeBuilder::Visit(const CAssignmentStatement *assignmentStatement) {
    assignmentStatement->Variable->Accept(this);
    CTypeInfo variableType = lastType;
    assignmentStatement->Expression->Accept(this);
    ExpPtr left = new TempExp(new CTemp(assignmentStatement->Variable->Identifier->Symbol));
    currNode = new MoveStatement(left, currNode);
    assert(variableType == lastType);
}

void CIRTreeBuilder::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {
    intArrayAssignmentStatement->Index->Accept(this);
    ExpPtr index = currNode;
    assert(lastType.VarType == TType::T_INT);
    intArrayAssignmentStatement->Expression->Accept(this);
    ExpPtr expr = currNode;
    assert(lastType.VarType == TType::T_INT);
    intArrayAssignmentStatement->Variable->Accept(this);
    ExpPtr  var = currNode;
    assert(lastType.VarType == TType::T_INT_ARRAY);
    ExpPtr shift = new BinopExp(BINOP::MUL, index, new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE));
    ExpPtr addr = new BinopExp(BINOP::PLUS, var, shift);
    currNode = new MoveStatement(new MemExp(addr), expr);
}

void CIRTreeBuilder::Visit(const CVarDeclaration *varDeclaration) {
    varDeclaration->Identifier->Accept(this);
    varDeclaration->Type->Accept(this);
}

void CIRTreeBuilder::Visit(const CVarDeclarationList *varDeclarationList) {
    varDeclarationList->VarDeclaration->Accept(this);
    if (varDeclarationList->Next != nullptr) {
        varDeclarationList->Next->Accept(this);
    }
}

void CIRTreeBuilder::Visit(const CBracketExpression *bracketExpression) {
    bracketExpression->Expression->Accept(this);
}

void CIRTreeBuilder::Visit(const CMethodArgumentsList *methodArgumentsList) {
    methodArgumentsList->VarDeclaration->Accept(this);
    if (methodArgumentsList->Next != nullptr) {
        methodArgumentsList->Next->Accept(this);
    }
}

void CIRTreeBuilder::Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration) {
    if (methodHeaderDeclaration->MethodArgumentList != nullptr) {
        methodHeaderDeclaration->MethodArgumentList->Accept(this);
    }
    methodHeaderDeclaration->MethodName->Accept(this);
    methodHeaderDeclaration->ReturnType->Accept(this);
}

void CIRTreeBuilder::Visit(const CMethodBodyDeclaration *methodBodyDeclaration) {
    methodBodyDeclaration->ReturnExpression->Accept(this);
    ExpPtr returnExp = currNode;
    if (methodBodyDeclaration->VarDeclarationList != nullptr) {
        methodBodyDeclaration->VarDeclarationList->Accept(this);
    }
    if (methodBodyDeclaration->StatementList != nullptr) {
        methodBodyDeclaration->StatementList->Accept(this);
    }
    currNode = new ESEQExp(currNode, returnExp);
}

void CIRTreeBuilder::Visit(const CMethodDeclaration *methodDeclaration) {
    const CSymbol* methodSymbol = methodDeclaration->MethodHeaderDeclaration->MethodName->Symbol;
    currentMethod = table.FindMethodInfo(currentClass.Name, methodSymbol);
    methodDeclaration->MethodHeaderDeclaration->Accept(this);
    methodDeclaration->MethodBodyDeclaration->Accept(this);
    functions.push_back(Function(currNode, genFunctionName(currentClass.Name, methodSymbol)));
}

void CIRTreeBuilder::Visit(const CMethodDeclarationList *methodDeclarationList) {
    methodDeclarationList->MethodDeclaration->Accept(this);
    if (methodDeclarationList->MethodDeclarationList != nullptr) {
        methodDeclarationList->MethodDeclarationList->Accept(this);
    }
}

void CIRTreeBuilder::Visit(const CClassDeclaration *classDeclaration) {
    const CSymbol* classSymbol = classDeclaration->ClassName->Symbol;
    auto iter = table.FindClass(classSymbol);
    assert(iter != table.Classes.end());
    currentClass = *iter;
    if (classDeclaration->BaseClassName != nullptr) {
        classDeclaration->BaseClassName->Accept(this);
    }
    classDeclaration->ClassName->Accept(this);
    if (classDeclaration->VarDeclarationList != nullptr) {
        classDeclaration->VarDeclarationList->Accept(this);
    }
    if (classDeclaration->MethodDeclarationList != nullptr) {
        classDeclaration->MethodDeclarationList->Accept(this);
    }
}

void CIRTreeBuilder::Visit(const CMainClass *mainClass) {
    mainClass->ArgumentName->Accept(this);
    mainClass->ClassName->Accept(this);
    mainClass->MainFunctionStatement->Accept(this);
    functions.push_back(Function(currNode, storage.Get(getMainFuncName())));
}

void CIRTreeBuilder::Visit(const CClassDeclarationList *classDeclarationList) {
    classDeclarationList->ClassDeclaration->Accept(this);
    if (classDeclarationList->ClassDeclarationList != nullptr) {
        classDeclarationList->ClassDeclarationList->Accept(this);
    }
}

void CIRTreeBuilder::Visit(const CGoal *goal) {
    goal->MainClass->Accept(this);
    if (goal->ClassDeclarationList != nullptr) {
        goal->ClassDeclarationList->Accept(this);
    }
}
