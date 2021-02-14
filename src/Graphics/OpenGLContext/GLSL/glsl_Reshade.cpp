#include "glsl_Reshade.h"

#include "Reshade/effect_parser.hpp"
#include "Reshade/effect_codegen.hpp"
#include "Reshade/effect_preprocessor.hpp"

using namespace glsl;

#include <iostream>

ReshadeShader::ReshadeShader(const opengl::GLInfo & _glinfo)
{
    /* TODO, fix this :) */

    reshadefx::preprocessor preprocessor;
    reshadefx::parser parser;
    reshadefx::module module;

    
    preprocessor.add_macro_definition("__RESHADE__", std::to_string(INT_MAX));
    preprocessor.add_macro_definition("__RESHADE_PERFORMANCE_MODE__", "1");
    /* huh? */
    preprocessor.add_macro_definition("__RENDERER__", "0x20000");    

    /* TODO */
    preprocessor.add_macro_definition("BUFFER_WIDTH", "640");
    preprocessor.add_macro_definition("BUFFER_HEIGHT", "480");
    preprocessor.add_macro_definition("BUFFER_RCP_WIDTH", "(1.0 / BUFFER_WIDTH)");
    preprocessor.add_macro_definition("BUFFER_RCP_HEIGHT", "(1.0 / BUFFER_HEIGHT)");
    /* thonk ? */
   // preprocessor.add_macro_definition("BUFFER_COLOR_DEPTH", "8");

    /* TODO */
    preprocessor.add_include_path("/home/rosalie/dev/reshade-shaders/Shaders/");


    if (!preprocessor.append_file("/home/rosalie/dev/reshade-shaders/Shaders/FilmGrain.fx"))
    {
        printf("FAILED TO LOAD SHADER FILE AAAA\n");
    }

    std::string errors = preprocessor.errors();
    if (errors != "")
    {
        std::cout << "PREPROCESSOR FAIL AAAAAAA: " << errors << std::endl;
        return;
    }

    std::unique_ptr<reshadefx::codegen> codegen(reshadefx::create_codegen_glsl(false, false));
    parser.parse(std::move(preprocessor.output()), codegen.get());

    errors = parser.errors();
    if (errors != "")
    {
        std::cout << "PARSER FAIL AAAAAAA: " << errors << std::endl;
        return;
    }

    codegen->write_result(module);

    std::cout << "CODEGEN OUT: " << module.hlsl << std::endl;

    m_part = module.hlsl;

    std::cout << "aaaaaaaa: " << module.textures.at(0).unique_name << std::endl;
    for (auto& m : module.uniforms)
    {
        std::cout <<  "UNIFORM: " << m.name << std::endl;
        std::cout <<  "UNIFORM: " << m.size << std::endl;

        for (auto& m1 : module.uniforms)
        {
            std::cout <<  "ANNOTATION: " << m1.name << std::endl;
            std::cout <<  "ANNOTATION: " << m1.size << std::endl;
            std::cout <<  "ANNOTATION: " << m1.type.description() << std::endl;
            std::cout <<  "ANNOTATION: " << m1.initializer_value.as_float[0] << std::endl;
        }
    }
    std::cout << "aaaa: " << module.total_uniform_size << std::endl;
}