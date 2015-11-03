//
// Created by nicolai on 03.11.15.
//

#ifndef MINIJAVACOMPILER_TREEBUILDHELP_H
#define MINIJAVACOMPILER_TREEBUILDHELP_H

#include "Declaration.h"

struct TVarAndStatementDeclaration {
        CVarDeclarationList* varDeclList;
        CStatementList* statementList;
    };

    struct TVarAndMethodDeclaration {
        CVarDeclarationList* varDeclList;
        CMethodDeclarationList* methodDeclList;
    };

#endif //MINIJAVACOMPILER_TREEBUILDHELP_H
