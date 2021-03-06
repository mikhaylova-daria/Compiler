cmake_minimum_required(VERSION 3.3)
project(MiniJavaCompiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutput ${CMAKE_SOURCE_DIR}/src/bison.cpp)
IF(BISON_FOUND)
        ADD_CUSTOM_COMMAND(
                OUTPUT ${BisonOutput}
                COMMAND ${BISON_EXECUTABLE}
                --defines=${CMAKE_SOURCE_DIR}/src/tokens.h
                --output=${BisonOutput} -v -d
                ${CMAKE_SOURCE_DIR}/src/minijava.y
                COMMENT "Generating bison.cpp"
        )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutput ${CMAKE_SOURCE_DIR}/src/flex.cpp)
IF(FLEX_FOUND)
        ADD_CUSTOM_COMMAND(
                PRE_BUILD
                OUTPUT ${FlexOutput}
                COMMAND ${FLEX_EXECUTABLE}
                --outfile=${FlexOutput}
                ${CMAKE_SOURCE_DIR}/src/flex.l
                COMMENT "Generating flex.cpp"
        )
ENDIF()

set(SOURCE_FILES ${BisonOutput} ${FlexOutput}
        src/main.cpp src/tokens_processing.cpp
        src/tokens_processing.h src/Declaration.h
        src/JavaHelp.h src/Utils.cpp
        src/tree/MinijavaTree.h
        src/tree/Location.h
        src/tree/Visitor.h
        src/tree/Type.h
        src/tree/Expression.h
        src/tree/Invocation.h
        src/tree/Indentifier.h
        src/tree/NewExpression.h
        src/tree/Statment.h
        src/tree/Declaration.h
        src/tree/TreeBuildHelp.h
        src/visitors/CPrettyPrinter.cpp
        src/visitors/CPrettyPrinter.hpp
        src/visitors/type_checking/TypeChecker.cpp
        src/visitors/type_checking/TypeChecker.h
        src/visitors/type_checking/Table.h
        src/visitors/type_checking/SymbolTableBuilder.cpp
        src/visitors/type_checking/SymbolTableBuilder.h
        src/symbol/Symbol.h
        src/Utils/ConsolePrinter.hpp
        src/IR/tree/IRTree.hpp
        src/IR/tree/Expressions.hpp
        src/IR/tree/Statements.hpp
        src/IR/tree/IdHolder.cpp
        src/visitors/IRtree/CIRTreePrinter.cpp
        src/visitors/IRtree/CIRTreePrinter.hpp
        src/visitors/IRtree/IIRTreeVisitor.hpp
        src/IR/translate/translate.hpp
        src/visitors/CIRTreeBuilder.cpp
        src/visitors/CIRTreeBuilder.h
        src/frame/Temp.hpp
        src/frame/Temp.cpp
        src/frame/Frame.hpp
        src/visitors/IRtree/CIRTreePrinter.hpp
        src/visitors/IRtree/CIRTreePrinter.cpp
        src/visitors/IRtree/IIRTreeVisitor.hpp
        src/visitors/CPrinter2.hpp
        src/visitors/CPrinter2.cpp
        src/visitors/IRtree/CIRTreeCanonizator.h
        src/visitors/IRtree/CIRTreeCanonizator.cpp
        src/visitors/IRtree/CIRTreeLinearizator.h
        src/visitors/IRtree/CIRTreeLinearizator.cpp
        src/visitors/IRtree/CIRTreeJumpOptimizer.cpp
        src/visitors/IRtree/CIRTreeJumpOptimizer.h src/Instruction/Instruction.h
        src/visitors/IRtree/CIRTreeCodeGenerator.h src/visitors/IRtree/CIRTreeCodeGenerator.cpp
        src/Instruction/Instruction.cpp
        src/Instruction/ControlFlowGraph.h
        src/Instruction/ControlFlowGraph.cpp
        src/Instruction/VarInteractGraph.h
        src/Instruction/VarInteractGraph.cpp
        src/Instruction/RegisterMapper.h
        src/Instruction/InstructionOperations.hpp
        src/Instruction/InstructionOperations.cpp
        src/visitors/IRtree/CIRTreeLin.h src/visitors/IRtree/CIRTreeLin.cpp)

add_executable(mjc ${SOURCE_FILES})
add_subdirectory(tests)
