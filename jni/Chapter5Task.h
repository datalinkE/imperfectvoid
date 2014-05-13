#ifndef CHAPTER5TASK_H_
#define CHAPTER5TASK_H_

#include "Task.hpp"
#include "Renderable/Geometry/Geometry.h"
#include "Renderable/Textures/Texture.h"
#include "Renderable/Shaders/TextureShaderProgram.h"
#include "Renderable/Renderable.h"
#include "Util/File.h"

class Renderer;


class Chapter5Task
	:	public Task
{
private:
	enum State
	{
		LOADING_FILE,
		CREATE_TEXTURE,
		RUNNING
	};

	State						m_state;

	Util::File				m_file;
	Renderer*		m_pRenderer;
	Geometry			m_geometry;
	TextureShaderProgram	m_textureShader;
	Renderable		m_renderable;
	Texture			m_texture;

	void*					m_pTGABuffer;
	unsigned int			m_readBytes;
	unsigned int			m_fileLength;

public:
	Chapter5Task(Renderer* pRenderer, const unsigned int priority);
	virtual ~Chapter5Task();

	// From Task
	virtual bool	Start();
	virtual void	OnSuspend();
	virtual void	Update();
	virtual void	OnResume();
	virtual void	Stop();

public:
	virtual std::string getName()		{ return "Chapter 5"; }
};

#endif // CHAPTER5TASK_H_
