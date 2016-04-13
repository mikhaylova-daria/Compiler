//
// Created by nicolai on 12.04.16.
//

#ifndef MINIJAVACOMPILER_CIRTREECODEGENERATOR_H
#define MINIJAVACOMPILER_CIRTREECODEGENERATOR_H


#include "IIRTreeVisitor.hpp"
#include "../../Instruction/Instruction.h"

namespace IRTree {

    class CIRTreeCodeGenerator : public IIRTreeVisitor {

    public:

        CIRTreeCodeGenerator( CStorage& storage, int bytes = 4) : storage(storage), Bytes(bytes) {}

        CodeGeneration::CCode Generate( StatementPtr ptr );

        virtual void Visit(const MoveStatement *moveStatement) override;

        virtual void Visit(const ExpressionStatement *expressionStatement) override;

        virtual void Visit(const JumpStatement *jumpStatement) override;

        virtual void Visit(const CJumpStatement *cJumpStatement) override;

        virtual void Visit(const SEQStatement *seqStatement) override;

        virtual void Visit(const StatementList *statementList) override;

        virtual void Visit(const LabelStatement *labelStatement) override;

        virtual void Visit(const ConstExp *constExp) override;

        virtual void Visit(const PlatformConstExp *platformConstExp) override;

        virtual void Visit(const NameExp *nameExp) override;

        virtual void Visit(const TempExp *tempExp) override;

        virtual void Visit(const BinopExp *binopExp) override;

        virtual void Visit(const MemExp *memExp) override;

        virtual void Visit(const ExpList *expList) override;

        virtual void Visit(const CallExp *callExp) override;

        virtual void Visit(const ESEQExp *eseqExp) override;
    private:
        const int Bytes;
        CodeGeneration::CCode code;
        CStorage& storage;
        CTempPtr target;

        std::string toStr(CJUMP op) {
            switch (op) {
                case J_EQ: return "je";
                case J_NE: return "jne";
                case J_LT: return "jl";
                case J_GT: return "jg";
                case J_LE: return "jle";
                case J_GE: return "jge";
                case J_ULT: return "jb";
                case J_UGT: return "ja";
                case J_ULE: return "jae";
                case J_UGE: return "jbe";
                default: assert(false);
            }
            return "";
        }
    };
}

#endif //MINIJAVACOMPILER_CIRTREECODEGENERATOR_H
