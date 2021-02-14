#!/usr/bin/env bash
set -ex

BASE_URL="https://raw.githubusercontent.com/crosire/reshade/main/source"

FILES=(
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
    effect_symbol_table_intrinsics.inl
    effect_token.hpp
)

for f in ${FILES[@]}
do
    curl -LO "$BASE_URL/$f"
done

