//
// Created by nicolai on 17.11.15.
//

#include "CIRTreeBuilder.h"
//#include "../frame/Frame.hpp"
#include <cmath>

using namespace IRTree;

typedef std::shared_ptr<ISubtreeWrapper> NodePtr;

void CIRTreeBuilder::Visit(const CConstant *constant) {
    if (constant->Type->Type == TType::T_INT) {
        currNode = NodePtr(new CExpConverter(ExpPtr(new ConstExp(std::stoi(constant->Value)))));
    } else if (constant->Type->Type == TType::T_BOOL) {
        currNode = NodePtr(new CExpConverter(ExpPtr(new ConstExp(constant->Value == "true"))));
    } else {
        assert(false);
    }
    constant->Type->Accept(this);
}

// возвращает значение, записанное в переменной. а не адрес
void CIRTreeBuilder::Visit(const CVariable *variable) {
    variable->Identifier->Accept(this);
    CVarInfo varInfo = currentMethod.FindVarInfo(variable->Identifier->Symbol);
    if (varInfo.VarName == nullptr) {
        varInfo = table.FindVarInfo(currentClass.Name, variable->Identifier->Symbol);
        assert(varInfo.VarName != nullptr);
        // так как член класса может жить в регистре, передаем сдвиг
        // если в регистре не будет значения, то придется добавить код для вычисления адреса относитьельно this
        int shift = table.FindVarPosition(currentClass.Name, variable->Identifier->Symbol);
        CTempPtr tempPtr(new Temp::CTemp(storage.Get("this"))); //genClassVarName(variable->Identifier->Symbol)));
        currNode = getNode(ExpPtr(new TempExp(tempPtr, shift)));
    } else {
        // заворачиваем в Temp, т.к. значение может жить в памяти или в регистре
        currNode = getNode(ExpPtr(new TempExp(CTempPtr(new Temp::CTemp(variable->Identifier->Symbol)), 0)));
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
    ExpPtr leftExpr = currNode->ToExp();
    binaryExpression->RightExpr->Accept(this);
    ExpPtr rightExpr = currNode->ToExp();

    static_assert(TBinaryExpression::BE_COUNT == 7, "TBinaryExpression switch failed");
    switch (binaryExpression->BinaryExpressionType) {
        case TBinaryExpression::BE_AND :
            currNode = NodePtr(new CExpConverter(ExpPtr(new BinopExp(BINOP::AND, leftExpr, rightExpr))));
            break;
        case TBinaryExpression::BE_EQUAL :
            currNode = NodePtr(new CExpConverter(ExpPtr(new BinopExp(BINOP::EQ, leftExpr, rightExpr))));
            lastType = CTypeInfo(storage.Get("boolean"), TType::T_BOOL);
            break;
        case TBinaryExpression::BE_LESS :
            currNode = NodePtr(new CExpConverter(ExpPtr(new BinopExp(BINOP::LT, leftExpr, rightExpr))));
            lastType = CTypeInfo(storage.Get("boolean"), TType::T_BOOL);
            break;
        case TBinaryExpression::BE_MINUS :
            currNode = NodePtr(new CExpConverter(ExpPtr(new BinopExp(BINOP::MINUS, leftExpr, rightExpr))));
            break;
        case TBinaryExpression::BE_MULTIPLICATION :
            currNode = NodePtr(new CExpConverter(ExpPtr(new BinopExp(BINOP::MUL, leftExpr, rightExpr))));
            break;
        case TBinaryExpression::BE_PLUS:
            currNode = NodePtr(new CExpConverter(ExpPtr(new BinopExp(BINOP::PLUS, leftExpr, rightExpr))));
            break;
        case TBinaryExpression::BE_SQ_BRACKETS : {
            // leftExpr - массив, в нем хранится адрес переменной
            ExpPtr sizeBinop = ExpPtr(new BinopExp(BINOP::MUL,
                                                   ExpPtr(new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE)),
                                                   rightExpr));
            // приняли значение, значит leftExpr не нужно разыменовывать
            currNode = NodePtr(new CExpConverter(ExpPtr(new MemExp(ExpPtr(new BinopExp(BINOP::PLUS, leftExpr, sizeBinop))))));
            break;
        } default:
            assert(false);
    }
}

void CIRTreeBuilder::Visit(const CNotExpression *notExpression) {
    notExpression->Expression->Accept(this);
    // currNode - значение
    currNode = getNode(ExpPtr(new BinopExp(BINOP::EQ, currNode->ToExp(), ExpPtr(new ConstExp(0)))));
    assert(lastType.VarType == TType::T_BOOL);
}

void CIRTreeBuilder::Visit(const CLengthExpression *lengthExpression) {
    lengthExpression->Expression->Accept(this);
    assert(lastType.VarType == TType::T_INT_ARRAY);
    // размер лежит в currNode[-1]
    ExpPtr binop = ExpPtr(new BinopExp(BINOP::MINUS,
                                       currNode->ToExp(),
                                       ExpPtr(new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE))));
    currNode = getNode(ExpPtr(new MemExp(binop)));
    lastType = CTypeInfo(storage.Get("int"), TType::T_INT);
}

void CIRTreeBuilder::Visit(const CExpressionList *expressionList) {
    expressionList->Expression->Accept(this);
    ExpPtr leftExpr = currNode->ToExp();
    if (expressionList->ExpressionList != nullptr) {
        expressionList->ExpressionList->Accept(this);
        currNode = getNode(ExpListPtr(new ExpList(leftExpr, currNode->ToExpList())));
    } else {
        currNode = getNode(ExpListPtr(new ExpList(leftExpr, nullptr)));
    }
}

void CIRTreeBuilder::Visit(const CIdentifier *) {

}

void CIRTreeBuilder::Visit(const CInvocation *invocation) {
    ExpListPtr callList;
    if (invocation->ExpressionList != nullptr) {
        invocation->ExpressionList->Accept(this);
        callList = currNode->ToExpList();
    } else {
        callList = nullptr;
    }
    invocation->Identifier->Accept(this);
    invocation->Expression->Accept(this);
    assert(lastType.VarType == TType::T_CLASS);
    const CSymbol* methodBase = table.FindMethodBase(lastType.TypeName, invocation->Identifier->Symbol);
    assert(methodBase != nullptr);
    const CSymbol* funcName = genFunctionName(methodBase, invocation->Identifier->Symbol);
    currNode = getNode(ExpPtr(new CallExp(NameExpPtr(new NameExp(LabelPtr(new CLabel(funcName)))), callList)));
    lastType = table.FindMethodInfo(lastType.TypeName, invocation->Identifier->Symbol).ReturnType;
    assert(lastType.TypeName != nullptr);
}

void CIRTreeBuilder::Visit(const CNewExpression *newExpression) {
    newExpression->Id->Accept(this);

    int size = table.FindClassSize(newExpression->Id->Symbol);
    assert(size != NOT_FOUND);
    currNode = getNode(ExpPtr(new CallExp(NameExpPtr(new NameExp(LabelPtr(new CLabel(storage.Get(getNewFuncName()))))),
                                          ExpListPtr(new ExpList(ExpPtr(new ConstExp(size)), nullptr)))));
    // инициализация
    currNode = getNode(buildZeroInitTree(currNode->ToExp(), size));
    auto classIterator = table.FindClass(newExpression->Id->Symbol);
    const CClassInfo& classInfo = *classIterator;
    lastType = CTypeInfo(classInfo.Name, TType::T_CLASS);
}

void CIRTreeBuilder::Visit(const CIntArrayNewExpression *intArrayNewExpression) {
    intArrayNewExpression->Expression->Accept(this);
    assert(lastType.VarType == TType::T_INT);
    ExpPtr size = currNode->ToExp();
    currNode = getNode(ExpPtr(new CallExp(NameExpPtr(new NameExp(LabelPtr(new CLabel(storage.Get(getNewFuncName()))))),
                                          ExpListPtr(new ExpList(size, nullptr)))));
    // инициализация
    currNode = getNode(buildZeroInitTree(currNode->ToExp(), size));
    lastType = CTypeInfo(storage.Get("int[]"), TType::T_INT_ARRAY);
}

void CIRTreeBuilder::Visit(const CStatementList *statementList) {
    statementList->Statement->Accept(this);
    StatementPtr leftStm = currNode->ToStm();

    if (statementList->StatementList != nullptr) {
        statementList->StatementList->Accept(this);
        currNode = getNode(StatementPtr(new SEQStatement(leftStm, currNode->ToStm())));
        //currNode = getNode(StatementPtr(new StatementList(leftStm, std::dynamic_pointer_cast<StatementList>(currNode->ToStm()))));
    } else {
        //currNode = getNode()
        //currNode = getNode(StatementPtr(new StatementList(leftStm, nullptr)));
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
    ExpPtr expPtr = currNode->ToExp();
    ifStatement->TrueStatement->Accept(this);
    StatementPtr trueStatement = currNode->ToStm();
    ifStatement->FalseStatement->Accept(this);
    StatementPtr falseStatement = currNode->ToStm();
    LabelPtr trueLabel(new Temp::CLabel(storage));
    LabelPtr falseLabel(new Temp::CLabel(storage));
    LabelPtr finLabel(new Temp::CLabel(storage));
    StatementPtr jump(new CJumpStatement(CJUMP::J_NE, expPtr, ExpPtr(new ConstExp(0)), trueLabel, falseLabel));
    /*
     * jump exp trueLab falseLab:
     *   trueLab
     *     trueSt
     *     jump fin
     *   falseLab
     *     falseSt
     *   finLab
     */
    StatementPtr root;
    root = StatementPtr(new SEQStatement(falseStatement, StatementPtr(new LabelStatement(finLabel))));
    root = StatementPtr(new SEQStatement(StatementPtr(new LabelStatement(falseLabel)), root));
    root = StatementPtr(new SEQStatement(StatementPtr(new JumpStatement({finLabel}, ExpPtr(new ConstExp(0)))), root));
    root = StatementPtr(new SEQStatement(trueStatement, root));
    root = StatementPtr(new SEQStatement(StatementPtr(new LabelStatement(trueLabel)), root));
    currNode = getNode(StatementPtr(new SEQStatement(jump, root)));
}

void CIRTreeBuilder::Visit(const CWhileStatement *whileStatement) {
    whileStatement->Expression->Accept(this);
    assert(lastType.VarType == TType::T_BOOL);
    ExpPtr exp = currNode->ToExp();
    whileStatement->Statement->Accept(this);
    StatementPtr statementPtr = currNode->ToStm();
    /*
     * whileLab
     * jump exp trueLab falseLab
     * trueLab
     * st
     * jump whileLab
     * falseLab
     */
    LabelPtr trueLabel(new Temp::CLabel(storage));
    LabelPtr falseLabel(new Temp::CLabel(storage));
    LabelPtr whileLabel(new Temp::CLabel(storage));
    StatementPtr jumpWhileLabel(new JumpStatement({whileLabel}, ExpPtr(new ConstExp(0))));
    StatementPtr jumpTrueFalseLabel(new CJumpStatement(CJUMP::J_NE, exp, ExpPtr(new ConstExp(0)), trueLabel, falseLabel));
    StatementPtr root;
    root = StatementPtr(new SEQStatement(jumpWhileLabel, StatementPtr(new LabelStatement(falseLabel))));
    root = StatementPtr(new SEQStatement(statementPtr, root));
    root = StatementPtr(new SEQStatement(StatementPtr(new LabelStatement(trueLabel)), root));
    root = StatementPtr(new SEQStatement(jumpTrueFalseLabel, root));
    currNode = getNode(StatementPtr(new SEQStatement(StatementPtr(new LabelStatement(whileLabel)), root)));
}

void CIRTreeBuilder::Visit(const CPrintStatement *printStatement) {
    printStatement->Expression->Accept(this);
    assert (lastType.VarType == TType::T_INT);
    currNode = getNode(ExpPtr(new CallExp(NameExpPtr(new NameExp(LabelPtr(new CLabel(storage.Get(getPrintFuncName()))))),
                                  ExpListPtr(currNode->ToExp(), nullptr))));
}

void CIRTreeBuilder::Visit(const CAssignmentStatement *assignmentStatement) {
    assignmentStatement->Variable->Accept(this);
    CTypeInfo variableType = lastType;
    assignmentStatement->Expression->Accept(this);
    ExpPtr left(new TempExp(CTempPtr(new CTemp(assignmentStatement->Variable->Identifier->Symbol)), 0));
    currNode = getNode(StatementPtr(new MoveStatement(left, currNode->ToExp())));
    assert(variableType == lastType);
}

void CIRTreeBuilder::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {
    intArrayAssignmentStatement->Index->Accept(this);
    ExpPtr index = currNode->ToExp();
    assert(lastType.VarType == TType::T_INT);
    intArrayAssignmentStatement->Expression->Accept(this);
    ExpPtr expr = currNode->ToExp();
    assert(lastType.VarType == TType::T_INT);
    intArrayAssignmentStatement->Variable->Accept(this);
    ExpPtr  var = currNode->ToExp();
    assert(lastType.VarType == TType::T_INT_ARRAY);
    ExpPtr shift(new BinopExp(BINOP::MUL, index, ExpPtr(new PlatformConstExp(TPlatformConstType::PCT_POINTER_SIZE))));
    ExpPtr addr(new BinopExp(BINOP::PLUS, var, shift));
    currNode = getNode(StatementPtr(new MoveStatement(ExpPtr(new MemExp(addr)), expr)));
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
    ExpPtr returnExp = currNode->ToExp();
    if (methodBodyDeclaration->VarDeclarationList != nullptr) {
        methodBodyDeclaration->VarDeclarationList->Accept(this);
    }
    if (methodBodyDeclaration->StatementList != nullptr) {
        methodBodyDeclaration->StatementList->Accept(this);
    }
    currNode = getNode(ExpPtr(new ESEQExp(currNode->ToStm(), returnExp)));
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
