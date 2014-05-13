#include "TextureShaderProgram.h"
#include <cassert>
#include "../Geometry/Geometry.h"
#include "../Textures/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TextureShaderProgram::TextureShaderProgram()
	:	m_pTexture(NULL)
	,	m_modelHandle(GL_INVALID_VALUE)
	,	m_samplerHandle(GL_INVALID_VALUE)
	,	m_texCoordAttributeHandle(GL_INVALID_VALUE)
	,	m_positionAttributeHandle(GL_INVALID_VALUE)
{
	m_vertexShaderCode =
			"uniform mat4 u_mModel; \n"
			"attribute vec4 a_vPosition;        \n"
			"attribute vec2 a_texCoord;         \n"
			"varying   vec2 v_texCoord;         \n"
			"void main(){                       \n"
			"    gl_Position = u_mModel * a_vPosition;		\n"
			"    v_texCoord = a_texCoord;		\n"
			"}                                  \n";

	m_fragmentShaderCode =
			"precision highp float;    							\n"
			"varying vec2 v_texCoord;								\n"
			"uniform sampler2D s_texture;							\n"
			"void main(){                							\n"
			"    gl_FragColor = texture2D(s_texture, v_texCoord);   \n"
			"}                         								\n";
}

TextureShaderProgram::~TextureShaderProgram()
{

}

void TextureShaderProgram::Link()
{
	ShaderProgram::Link();

	m_positionAttributeHandle	= glGetAttribLocation(m_programId, "a_vPosition");
	m_texCoordAttributeHandle	= glGetAttribLocation(m_programId, "a_texCoord");
	m_samplerHandle				= glGetUniformLocation(m_programId, "s_texture");
	m_modelHandle				= glGetUniformLocation(m_programId, "u_mModel");
}

void TextureShaderProgram::Setup(Renderable& renderable)
{
	assert(m_pTexture);
	Geometry* pGeometry = renderable.GetGeometry();
	if (pGeometry && m_pTexture)
	{
		ShaderProgram::Setup(renderable);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->GetId());
		glUniform1i(m_samplerHandle, 0);
		float ratio = 480.0f / 800.0f;
		glm::mat4 projection = glm::ortho<GLfloat>( -1.0f, 1.0f, -ratio, ratio, -1.0f, 1.0f );
		glm::mat4 model = glm::rotate(glm::mat4(1), 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		glm::mat4 mvp = projection * model;
		glUniformMatrix4fv(m_modelHandle, 1, false, glm::value_ptr(mvp));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glVertexAttribPointer(
				m_positionAttributeHandle,
				pGeometry->GetNumVertexPositionElements(),
				GL_FLOAT,
				GL_FALSE,
				pGeometry->GetVertexStride(),
				pGeometry->GetVertexBuffer());
		glEnableVertexAttribArray(m_positionAttributeHandle);

		glVertexAttribPointer(
				m_texCoordAttributeHandle,
				pGeometry->GetNumTexCoordElements(),
				GL_FLOAT,
				GL_FALSE,
				pGeometry->GetVertexStride(),
				&static_cast<GLfloat*>(pGeometry->GetVertexBuffer())[pGeometry->GetNumVertexPositionElements()]);
		glEnableVertexAttribArray(m_texCoordAttributeHandle);
	}
}

