//
// Created by nicolai on 03.11.15.
//

#include "TypeChecker.h"

extern void printTextPart(Location loc, std::ostream &out = std::cout);

void CTypeChecker::Visit(const CType* type) {
    if (type->Type == TType::T_CLASS && !isContain<CClassInfo,&CClassInfo::Name>(table.Classes, type->Name)) {
        processError("unable to find class '" + type->Name->GetName() + "'", type);
    }
    lastType = CTypeInfo(type->Name, type->Type);
}

void CTypeChecker::Visit(const CVariable* variable) {
    variable->Identifier->Accept(this);
    if (!isContain<CVarInfo,&CVarInfo::VarName>(currentMethod.Arguments, variable->Identifier->Symbol)
                && !isContain<CVarInfo,&CVarInfo::VarName>(currentMethod.Vars, variable->Identifier->Symbol)
                && !isContain<CVarInfo,&CVarInfo::VarName>(currentClass.Vars, variable->Identifier->Symbol)) {
        processError("undefined variable '" + variable->Identifier->Symbol->GetName() + "'", variable);
    }
    const CSymbol* vasSymbol = variable->Identifier->Symbol;
    auto varIterator = find<CVarInfo,&CVarInfo::VarName>(currentMethod.Arguments, vasSymbol);
    if (varIterator == currentMethod.Arguments.end()) {
        varIterator = find<CVarInfo,&CVarInfo::VarName>(currentMethod.Vars, vasSymbol);
        if (varIterator == currentMethod.Vars.end()) {
            varIterator = find<CVarInfo,&CVarInfo::VarName>(currentClass.Vars, vasSymbol);
            if (varIterator == currentClass.Vars.end()) {
                processError("undefined varialbe '" + vasSymbol->GetName() + "'", variable);
                return;
            }
        }
    }
    lastType = CTypeInfo(varIterator->TypeInfo);
}

void CTypeChecker::Visit(const CConstant *constant) {
    constant->Type->Accept(this);
    lastType = CTypeInfo(constant->Type->Name, constant->Type->Type);
}

void CTypeChecker::Visit(const CBinaryExpression *binaryExpression) {
    binaryExpression->LeftExpr->Accept(this);
    CTypeInfo typeInfo = lastType;
    binaryExpression->RightExpr->Accept(this);

    static_assert(TType::T_COUNT == 4, "TType switch failed");
    switch (binaryExpression->BinaryExpressionType) {
        case TBinaryExpression::BE_AND :
        case TBinaryExpression::BE_EQUAL :
            if (lastType != typeInfo || lastType.VarType != TType::T_BOOL) {
                processError("expected boolean type expressions", binaryExpression);
            }
            break;
        case TBinaryExpression::BE_LESS :
            if (lastType != typeInfo || lastType.VarType != TType::T_INT) {
                processError("expected int type expressions", binaryExpression);
            }
            lastType = CTypeInfo(storage.Get("boolean"), TType::T_BOOL);
            break;
        case TBinaryExpression::BE_MINUS :
        case TBinaryExpression::BE_MULTIPLICATION :
        case TBinaryExpression::BE_PLUS:
            if (lastType != typeInfo || lastType.VarType != TType::T_INT) {
                processError("expected int type expressions", binaryExpression);
            }
            break;
        case TBinaryExpression::BE_SQ_BRACKETS :
            if (typeInfo.VarType != TType::T_INT_ARRAY || lastType.VarType != TType::T_INT) {
                processError("expected int[] and int type expressions", binaryExpression);
                lastType = typeInfo;
            }
            break;
        default:
            assert(false);
    }
}

void CTypeChecker::Visit(const CNotExpression *notExpression) {
    notExpression->Expression->Accept(this);
    if (lastType.VarType != TType::T_BOOL) {
        processError("expected boolean expression", notExpression);
    }
}

void CTypeChecker::Visit(const CLengthExpression *lengthExpression) {
    lengthExpression->Expression->Accept(this);
    if (lastType.VarType != TType::T_CLASS) {
        processError("expected class expression", lengthExpression);
    }
    lastType = CTypeInfo(storage.Get("int"), TType::T_INT);
}

void CTypeChecker::Visit(const CExpressionList *expressionList) {
    expressionList->Expression->Accept(this);
    lastTypeList.push_back(lastType);
    if (expressionList->ExpressionList != nullptr) {
        expressionList->ExpressionList->Accept(this);
    }
}

void CTypeChecker::Visit(const CIdentifier*) {

}

void CTypeChecker::Visit(const CInvocation *invocation) {
    invocation->Expression->Accept(this);
    if (lastType.VarType != TType::T_CLASS) {
        processError("expected class expression", invocation);
        invocation->ExpressionList->Accept(this);
        invocation->Identifier->Accept(this);
        lastType = CTypeInfo(storage.Get("int"), TType::T_INT);
        return;
    }

    auto classIterator = find<CClassInfo, &CClassInfo::Name>(table.Classes, lastType.TypeName);
    if (classIterator == table.Classes.end()) {
        processError("unexpected class name '" + lastType.TypeName->GetName() + "'", invocation);
        invocation->ExpressionList->Accept(this);
        invocation->Identifier->Accept(this);
        lastType = CTypeInfo(storage.Get("int"), TType::T_INT);
        return;
    }
    const CClassInfo& classInfo = *classIterator;

    invocation->Identifier->Accept(this);
    auto methodIterator = find<CMethodInfo,&CMethodInfo::Name>(classInfo.Methods, invocation->Identifier->Symbol);
    if (methodIterator == classInfo.Methods.end()) {
        processError("unable to find method '" + invocation->Identifier->Symbol->GetName() + "' in class '"
                + classInfo.Name->GetName() + "'", invocation);
        invocation->ExpressionList->Accept(this);
        lastType = CTypeInfo(storage.Get("int"), TType::T_INT);
        return;
    }
    const CMethodInfo& methodInfo = *methodIterator;

    lastTypeList.clear();
    if (invocation->ExpressionList != nullptr) {
        invocation->ExpressionList->Accept(this);
    }
    if (!isComplementaryTypes(methodInfo.Arguments, lastTypeList)) {
        processError("invalid invoation arguments type", invocation);
    }
    lastType = methodInfo.ReturnType;
}

void CTypeChecker::Visit(const CNewExpression *newExpression) {
    newExpression->Id->Accept(this);
    auto classIterator = find<CClassInfo, &CClassInfo::Name>(table.Classes, newExpression->Id->Symbol);
    if (classIterator == table.Classes.end()) {
        processError("unexpected class name '" + lastType.TypeName->GetName() + "'", newExpression);
    }
    const CClassInfo& classInfo = *classIterator;
    lastType = CTypeInfo(classInfo.Name, TType::T_CLASS);
}

void CTypeChecker::Visit(const CIntArrayNewExpression *intArrayNewExpression) {
    intArrayNewExpression->Expression->Accept(this);
    if (lastType.VarType != TType::T_INT) {
        processError("expected int experssion", intArrayNewExpression);
    }
    lastType = CTypeInfo(storage.Get("int[]"), TType::T_INT_ARRAY);
}

void CTypeChecker::Visit(const CStatementList *statementList) {
    statementList->Statement->Accept(this);
    if (statementList->StatementList != nullptr) {
        statementList->StatementList->Accept(this);
    }
}

void CTypeChecker::Visit(const CBracketStatement *bracketStatement) {
    if (bracketStatement->StatementList != nullptr) {
        bracketStatement->StatementList->Accept(this);
    }
}

void CTypeChecker::Visit(const CIfStatement *ifStatement) {
    ifStatement->Expression->Accept(this);
    if (lastType.VarType != TType::T_BOOL) {
        processError("expected bool experssion", ifStatement);
    }
    ifStatement->TrueStatement->Accept(this);
    ifStatement->FalseStatement->Accept(this);
}

void CTypeChecker::Visit(const CWhileStatement *whileStatement) {
    whileStatement->Expression->Accept(this);
    if (lastType.VarType != TType::T_BOOL) {
        processError("expected bool experssion", whileStatement);
    }
    whileStatement->Statement->Accept(this);
}

void CTypeChecker::Visit(const CPrintStatement *printStatement) {
    printStatement->Expression->Accept(this);
    if (lastType.VarType != TType::T_INT) {
        processError("expected int experssion", printStatement);
    }
}

void CTypeChecker::Visit(const CAssignmentStatement *assignmentStatement) {
    assignmentStatement->Identifier->Accept(this);
    assignmentStatement->Expression->Accept(this);

    const CSymbol* vasSymbol = assignmentStatement->Identifier->Symbol;
    auto varIterator = find<CVarInfo,&CVarInfo::VarName>(currentMethod.Arguments, vasSymbol);
    if (varIterator == currentMethod.Arguments.end()) {
        varIterator = find<CVarInfo,&CVarInfo::VarName>(currentMethod.Vars, vasSymbol);
        if (varIterator == currentMethod.Vars.end()) {
            varIterator = find<CVarInfo,&CVarInfo::VarName>(currentClass.Vars, vasSymbol);
            if (varIterator == currentClass.Vars.end()) {
                processError("undefined varialbe '" + vasSymbol->GetName() + "'", assignmentStatement);
                return;
            }
        }
    }
    const CVarInfo& varInfo = *varIterator;
    if (varInfo.TypeInfo != lastType) {
        processError("different types", assignmentStatement);
    }
}

void CTypeChecker::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {
    intArrayAssignmentStatement->Index->Accept(this);
    if (lastType.VarType != TType::T_INT) {
        processError("expected int type index", intArrayAssignmentStatement);
    }
    intArrayAssignmentStatement->Expression->Accept(this);
    if (lastType.VarType != TType::T_INT) {
        processError("expected int type value", intArrayAssignmentStatement);
    }

    const CSymbol* vasSymbol = intArrayAssignmentStatement->Identifier->Symbol;
    auto varIterator = find<CVarInfo,&CVarInfo::VarName>(currentMethod.Arguments, vasSymbol);
    if (varIterator == currentMethod.Arguments.end()) {
        varIterator = find<CVarInfo,&CVarInfo::VarName>(currentMethod.Vars, vasSymbol);
        if (varIterator == currentMethod.Vars.end()) {
            varIterator = find<CVarInfo,&CVarInfo::VarName>(currentClass.Vars, vasSymbol);
            if (varIterator == currentClass.Vars.end()) {
                processError("undefined varialbe '" + vasSymbol->GetName() + "'", intArrayAssignmentStatement);
                return;
            }
        }
    }
    const CVarInfo& varInfo = *varIterator;

    if (varInfo.TypeInfo.VarType != TType::T_INT_ARRAY) {
        processError("different types", intArrayAssignmentStatement);
    }
}

void CTypeChecker::Visit(const CVarDeclaration *varDeclaration) {
    varDeclaration->Identifier->Accept(this);
    varDeclaration->Type->Accept(this);
}

void CTypeChecker::Visit(const CVarDeclarationList *varDeclarationList) {
    varDeclarationList->VarDeclaration->Accept(this);
    if (varDeclarationList->Next != nullptr) {
        varDeclarationList->Next->Accept(this);
    }
}

void CTypeChecker::Visit(const CBracketExpression *bracketExpression) {
    bracketExpression->Expression->Accept(this);
}

void CTypeChecker::Visit(const CMethodArgumentsList *methodArgumentsList) {
    methodArgumentsList->VarDeclaration->Accept(this);
    if (methodArgumentsList->Next != nullptr) {
        methodArgumentsList->Next->Accept(this);
    }
}

void CTypeChecker::Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration) {
    if (methodHeaderDeclaration->MethodArgumentList != nullptr) {
        methodHeaderDeclaration->MethodArgumentList->Accept(this);
    }
    methodHeaderDeclaration->MethodName->Accept(this);
    methodHeaderDeclaration->ReturnType->Accept(this);
}

void CTypeChecker::Visit(const CMethodBodyDeclaration *methodBodyDeclaration) {
    methodBodyDeclaration->ReturnExpression->Accept(this);
    if (methodBodyDeclaration->VarDeclarationList != nullptr) {
        methodBodyDeclaration->VarDeclarationList->Accept(this);
    }
    if (methodBodyDeclaration->StatementList != nullptr) {
        methodBodyDeclaration->StatementList->Accept(this);
    }
}

void CTypeChecker::Visit(const CMethodDeclaration *methodDeclaration) {
    const CSymbol* methodSymbol = methodDeclaration->MethodHeaderDeclaration->MethodName->Symbol;
    currentMethod = *find<CMethodInfo,&CMethodInfo::Name>(currentClass.Methods, methodSymbol);
    methodDeclaration->MethodHeaderDeclaration->Accept(this);
    methodDeclaration->MethodBodyDeclaration->Accept(this);
}

void CTypeChecker::Visit(const CMethodDeclarationList *methodDeclarationList) {
    methodDeclarationList->MethodDeclaration->Accept(this);
    if (methodDeclarationList->MethodDeclarationList != nullptr) {
        methodDeclarationList->MethodDeclarationList->Accept(this);
    }
}

void CTypeChecker::Visit(const CClassDeclaration *classDeclaration) {
    const CSymbol* classSymbol = classDeclaration->ClassName->Symbol;
    currentClass = *find<CClassInfo,&CClassInfo::Name>(table.Classes, classSymbol);
    if (isCyclicInheritance(classSymbol)) {
        processError("cyclic inheritance for class '" + classSymbol->GetName() + "'", classDeclaration);
    }

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

void CTypeChecker::Visit(const CMainClass *mainClass) {
    mainClass->ArgumentName->Accept(this);
    mainClass->ClassName->Accept(this);
    mainClass->MainFunctionStatement->Accept(this);
}

void CTypeChecker::Visit(const CClassDeclarationList *classDeclarationList) {
    classDeclarationList->ClassDeclaration->Accept(this);
    if (classDeclarationList->ClassDeclarationList != nullptr) {
        classDeclarationList->ClassDeclarationList->Accept(this);
    }
}

void CTypeChecker::Visit(const CGoal *goal) {
    goal->MainClass->Accept(this);
    if (goal->ClassDeclarationList != nullptr) {
        goal->ClassDeclarationList->Accept(this);
    }
}

