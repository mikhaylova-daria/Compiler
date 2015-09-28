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
            --output=${BisonOutput}
            ${CMAKE_SOURCE_DIR}/src/bison.y
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

set(SOURCE_FILES ${BisonOutput} ${FlexOutput} src/main.cpp src/tokens_processing.cpp src/tokens_processing.h)

add_executable(mjc ${SOURCE_FILES})