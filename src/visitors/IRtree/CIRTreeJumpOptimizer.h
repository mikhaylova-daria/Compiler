//
// Created by nicolai on 11.04.16.
//

#ifndef MINIJAVACOMPILER_CIRTREEJUMPOPTIMIZER_H
#define MINIJAVACOMPILER_CIRTREEJUMPOPTIMIZER_H

#include <memory>
#include "IIRTreeVisitor.hpp"
#include "../../IR/tree/Statements.hpp"

namespace IRTree {

    class CIRTreeJumpOptimizer {
    public:
        CIRTreeJumpOptimizer( CStorage& storage ) : storage(storage) { }
        std::shared_ptr<StatementList> Optimize(const std::shared_ptr<StatementList>& list );
    private:
        CJUMP reverse(CJUMP op);
        CStorage& storage;
    };
}
#endif //MINIJAVACOMPILER_CIRTREEJUMPOPTIMIZER_H
