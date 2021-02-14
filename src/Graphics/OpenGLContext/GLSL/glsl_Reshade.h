#pragma once
#include "glsl_ShaderPart.h"
#include <Graphics/OpenGLContext/opengl_GLInfo.h>

namespace glsl {

	class ReshadeShader : public ShaderPart
	{
	public:
		ReshadeShader(const opengl::GLInfo & _glinfo);
	};

/*	class ReshadeShader : public graphics::ShaderProgram
	{
	public:
		ReshadeShader(const opengl::GLInfo & _glinfo,
			opengl::CachedUseProgram * _useProgram,
			const ShaderPart * _vertexHeader,
			const ShaderPart * _fragmentHeader,
			const ShaderPart * _fragmentEnd = nullptr)
			: m_program(0)
			, m_useProgram(_useProgram)
		{
			VertexBody vertexBody(_glinfo);
			FragmentBody fragmentBody(_glinfo);

			std::stringstream ssVertexShader;
			_vertexHeader->write(ssVertexShader);
			vertexBody.write(ssVertexShader);

			std::stringstream ssFragmentShader;
			_fragmentHeader->write(ssFragmentShader);
			fragmentBody.write(ssFragmentShader);
			if (_fragmentEnd != nullptr)
				_fragmentEnd->write(ssFragmentShader);

			m_program =
				graphics::ObjectHandle(Utils::createRectShaderProgram(ssVertexShader.str().data(), ssFragmentShader.str().data()));
		}

		~SpecialShader()
		{
			m_useProgram->useProgram(graphics::ObjectHandle::null);
			glDeleteProgram(GLuint(m_program));
		}

		void activate() override {
			m_useProgram->useProgram(m_program);
			gDP.changed |= CHANGED_COMBINE;
		}

	protected:
		graphics::ObjectHandle m_program;
		opengl::CachedUseProgram * m_useProgram;
	};*/
}