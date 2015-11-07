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

set(SOURCE_FILES ${BisonOutput} ${FlexOutput} src/main.cpp src/tokens_processing.cpp src/tokens_processing.h src/Declaration.h src/JavaHelp.h src/Utils.cpp src/tree/MinijavaTree.h src/tree/Location.h src/visitors/CPrinter.h src/visitors/CPrinter.cpp src/tree/Visitor.h src/tree/Type.h src/tree/Constant.h src/tree/Expression.h src/tree/Invocation.h src/tree/Indentifier.h src/tree/Assignment.h src/tree/NewExpression.h src/tree/Statment.h src/tree/Declaration.h src/tree/TreeBuildHelp.h src/visitors/TypeChecker.cpp src/visitors/TypeChecker.h src/Utils/ConsolePrinter.hpp src/visitors/CPrinter2.cpp src/visitors/CPrinter2.hpp)

add_executable(mjc ${SOURCE_FILES})