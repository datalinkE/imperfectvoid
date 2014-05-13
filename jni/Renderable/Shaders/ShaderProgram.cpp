#include "ShaderProgram.h"

ShaderProgram::ShaderProgram()
	:	m_vertexShaderId(GL_INVALID_VALUE)
	,	m_fragmentShaderId(GL_INVALID_VALUE)
	,	m_programId(GL_INVALID_VALUE)
	,	m_isLinked(false)
{

}

ShaderProgram::~ShaderProgram()
{

}

void ShaderProgram::LoadShader(GLuint id, std::string& shaderCode)
{
	static const uint32_t NUM_SHADERS = 1;

	const GLchar* pCode = shaderCode.c_str();
	GLint length = shaderCode.length();

	glShaderSource(id, NUM_SHADERS, &pCode, &length);

	glCompileShader(id);

	glAttachShader(m_programId, id);
}

void ShaderProgram::Link()
{
	m_programId = glCreateProgram();

	m_vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	LoadShader(m_vertexShaderId, m_vertexShaderCode);

	m_fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	LoadShader(m_fragmentShaderId, m_fragmentShaderCode);

	glLinkProgram(m_programId);

	m_isLinked = true;
}

void ShaderProgram::Setup(Renderable& renderable)
{
	glUseProgram(m_programId);
}

