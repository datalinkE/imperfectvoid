#ifndef RENDERABLE_H_
#define RENDERABLE_H_

class Geometry;
class ShaderProgram;
class Texture;

class Renderable
{
private:
	Geometry*	m_pGeometry;
	ShaderProgram*		m_pShader;

public:
	Renderable();
	~Renderable();

	void			SetGeometry(Geometry* pGeometry);
	Geometry*		GetGeometry();

	void			SetShader(ShaderProgram* pShader);
	ShaderProgram*	GetShader();
};

inline Renderable::Renderable()
	:	m_pGeometry(NULL)
	,	m_pShader(NULL)
{

}

inline Renderable::~Renderable()
{

}

inline void Renderable::SetGeometry(Geometry* pGeometry)
{
	m_pGeometry = pGeometry;
}

inline Geometry* Renderable::GetGeometry()
{
	return m_pGeometry;
}

inline void Renderable::SetShader(ShaderProgram* pShader)
{
	m_pShader = pShader;
}

inline ShaderProgram* Renderable::GetShader()
{
	return m_pShader;
}


#endif // RENDERABLE_H_
