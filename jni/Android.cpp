#include "Android.h"
#include "Renderer.h"
#include <assert.h>

bool Android::m_bClosing	= false;
bool Android::m_bPaused		= false;

boost::signals2::signal<void()> Android::sigInit;
boost::signals2::signal<void()> Android::sigDestroy;
boost::signals2::signal<void()> Android::sigTermWindow;

void Android::android_handle_cmd(struct android_app* app, int32_t cmd)
{
	switch (cmd)
	{
		case APP_CMD_INIT_WINDOW:
		{
			DLOG() << "APP_CMD_INIT_WINDOW";
			//Renderer* pRenderer = static_cast<Renderer*>(app->userData);
			//assert(pRenderer);
			//pRenderer->Init();
			sigInit();
		}
		break;

	case APP_CMD_DESTROY:
		{
			DLOG() << "APP_CMD_DESTROY";
			//Renderer* pRenderer = static_cast<Renderer*>(app->userData);
			//assert(pRenderer);
			//pRenderer->Destroy();
			sigDestroy();
		}
		break;

	case APP_CMD_TERM_WINDOW:
		{
			DLOG() << "APP_CMD_TERM_WINDOW";
			//Renderer* pRenderer = static_cast<Renderer*>(app->userData);
			//assert(pRenderer);
			//pRenderer->Destroy();
			sigTermWindow();
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

int Android::android_handle_input(struct android_app* app, AInputEvent* event)
{
	int handled = 0;
	if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
	{
		if (AInputEvent_getSource(event) == AINPUT_SOURCE_TOUCHSCREEN)
		{
			int action = AMotionEvent_getAction(event);
			if (action == AMOTION_EVENT_ACTION_DOWN)
			{
				//Framework::SendEvent(Framework::JUMP_EVENT);
				float tapX = AMotionEvent_getX(event, 0);
				float tapY = AMotionEvent_getY(event, 0);
				DLOG() << "tap at" << tapX << tapY;
				handled = 1;
			}
		}
	}
	return handled;
}

Android::Android(android_app* pState, unsigned int priority)
	:	Task(priority)
{
	DLOG();
	m_pState = pState;
	m_pState->onAppCmd = android_handle_cmd;
	m_pState->onInputEvent = android_handle_input;
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

