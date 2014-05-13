#ifndef TEXTURESHADER_H_
#define TEXTURESHADER_H_

#include "ShaderProgram.h"

class Texture;

class TextureShaderProgram
	:	public ShaderProgram
{
private:
	Texture*	m_pTexture;
	GLint		m_positionAttributeHandle;
	GLint		m_texCoordAttributeHandle;
	GLint		m_samplerHandle;
	GLint		m_modelHandle;

public:
	TextureShaderProgram();
	virtual ~TextureShaderProgram();

	virtual void Link();
	virtual void Setup(Renderable& renderable);

	void			SetTexture(Texture* pTexture);
	Texture*		GetTexture();
};

inline void TextureShaderProgram::SetTexture(Texture* pTexture)
{
	m_pTexture = pTexture;
}

inline Texture* TextureShaderProgram::GetTexture()
{
	return m_pTexture;
}


#endif // TEXTURESHADER_H_
