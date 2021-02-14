#
# Reshade CMakeLists.txt
#
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)

set (SOURCES
    effect_codegen.hpp
    effect_codegen_glsl.cpp
    effect_expression.cpp
    effect_expression.hpp
    effect_lexer.cpp
    effect_lexer.hpp
    effect_module.hpp
    effect_parser.hpp
    effect_parser_exp.cpp
    effect_parser_stmt.cpp
    effect_preprocessor.cpp
    effect_preprocessor.hpp
    effect_symbol_table.cpp
    effect_symbol_table.hpp
    #effect_symbol_table_intrinsics.inl
    effect_token.hpp
)

add_library(Reshade STATIC ${SOURCES})
