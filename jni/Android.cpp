#include "Android.h"
#include "Renderer.h"
#include <assert.h>

bool Android::m_bClosing	= false;
bool Android::m_bPaused		= false;

static void android_handle_cmd(struct android_app* app, int32_t cmd)
{
	switch (cmd)
	{
		case APP_CMD_INIT_WINDOW:
		{
			DLOG() << "APP_CMD_INIT_WINDOW";
			Renderer* pRenderer = static_cast<Renderer*>(app->userData);
			assert(pRenderer);
			pRenderer->Init();
		}
		break;

	case APP_CMD_DESTROY:
		{
			DLOG() << "APP_CMD_DESTROY";
			Renderer* pRenderer = static_cast<Renderer*>(app->userData);
			assert(pRenderer);
			pRenderer->Destroy();
		}
		break;

	case APP_CMD_TERM_WINDOW:
		{
			DLOG() << "APP_CMD_TERM_WINDOW";
			Renderer* pRenderer = static_cast<Renderer*>(app->userData);
			assert(pRenderer);
			pRenderer->Destroy();
		}
		break;

	case APP_CMD_RESUME:
		{
			DLOG() << "APP_CMD_RESUME";
			Android::SetPaused(false);
		}
		break;

	case APP_CMD_PAUSE:
		{
			DLOG() << "APP_CMD_PAUSE";
			Android::SetPaused(true);
		}
		break;
	}
}

Android::Android(android_app* pState, unsigned int priority)
	:	Task(priority)
{
	DLOG();
	m_pState = pState;
	m_pState->onAppCmd = android_handle_cmd;
}

Android::~Android()
{
	DLOG();
}

bool Android::Start()
{
	DLOG();
	return true;
}

void Android::OnSuspend()
{
	DLOG();
}

void Android::Update()
{
	//DLOG();
	int events;
	struct android_poll_source* pSource;
	int ident = ALooper_pollAll(0, 0, &events, (void**)&pSource);
	if (ident >= 0)
	{
		if (pSource)
		{
			pSource->process(m_pState, pSource);
		}

		if (m_pState->destroyRequested)
		{
			m_bClosing = true;
		}
	}
}

void Android::OnResume()
{
	DLOG();
}

void Android::Stop()
{
	DLOG();
}

