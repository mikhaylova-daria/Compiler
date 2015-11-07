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
                || !isContain<CVarInfo,&CVarInfo::VarName>(currentMethod.Vars, variable->Identifier->Symbol)
                || !isContain<CVarInfo,&CVarInfo::VarName>(currentClass.Vars, variable->Identifier->Symbol)) {
        processError("undefined variable '" + variable->Identifier->Symbol->GetName() + "'", variable);
    }
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
        case TBinaryExpression::BE_LESS :
            if (lastType != typeInfo && lastType.VarType != TType::T_BOOL) {
                processError("expected boolean type expressions", binaryExpression);
            }
            break;
        case TBinaryExpression::BE_MINUS :
        case TBinaryExpression::BE_MULTIPLICATION :
        case TBinaryExpression::BE_PLUS:
            if (lastType != typeInfo && lastType.VarType != TType::T_INT) {
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
    invocation->ExpressionList->Accept(this);
    if (!isComplementaryTypes(methodInfo.Vars, lastTypeList)) {
        processError("invalid invoation arguments type", invocation);
    }
    lastType = currentMethod.ReturnType;
}

void CTypeChecker::Visit(const CNewExpression *newExpression) {

}

void CTypeChecker::Visit(const CIntArrayNewExpression *intArrayNewExpression) {

}

void CTypeChecker::Visit(const CStatementList *statementList) {

}

void CTypeChecker::Visit(const CBracketStatement *bracketStatement) {

}

void CTypeChecker::Visit(const CIfStatement *ifStatement) {

}

void CTypeChecker::Visit(const CWhileStatement *whileStatement) {

}

void CTypeChecker::Visit(const CPrintStatement *printStatement) {

}

void CTypeChecker::Visit(const CAssignmentStatement *assignmentStatement) {

}

void CTypeChecker::Visit(const CIntArrayAssignmentStatement *intArrayAssignmentStatement) {

}

void CTypeChecker::Visit(const CVarDeclaration *varDeclaration) {

}

void CTypeChecker::Visit(const CVarDeclarationList *varDeclarationList) {

}

void CTypeChecker::Visit(const CBracketExpression *bracketExpression) {

}

void CTypeChecker::Visit(const CMethodArgumentsList *methodArgumentsList) {

}

void CTypeChecker::Visit(const CMethodHeaderDeclaration *methodHeaderDeclaration) {

}

void CTypeChecker::Visit(const CMethodBodyDeclaration *methodBodyDeclaration) {

}

void CTypeChecker::Visit(const CMethodDeclaration *methodDeclaration) {

}

void CTypeChecker::Visit(const CMethodDeclarationList *methodDeclarationList) {

}

void CTypeChecker::Visit(const CClassDeclaration *classDeclaration) {

}

void CTypeChecker::Visit(const CMainClass *mainClass) {

}

void CTypeChecker::Visit(const CClassDeclarationList *classDeclarationList) {

}

void CTypeChecker::Visit(const CGoal *goal) {

}

