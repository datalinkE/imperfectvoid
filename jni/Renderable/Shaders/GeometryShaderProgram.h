#ifndef BASICSHADER_H_
#define BASICSHADER_H_

#include "ShaderProgram.h"

class GeometryShaderProgram
	:	public ShaderProgram
{
private:
	GLint	m_positionAttributeHandle;

public:
	GeometryShaderProgram();
	virtual ~GeometryShaderProgram();

	virtual void Link();
	virtual void Setup(Renderable& renderable);
};

#endif // BASICSHADER_H_
