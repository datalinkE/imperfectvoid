#ifndef ANDROID_H_
#define ANDROID_H_

#include <android_native_app_glue.h>
#include "Task.hpp"
#include <boost/signals2.hpp>

class Android
	:	public Task
{
private:
	static bool		m_bClosing;
	static bool		m_bPaused;
	android_app*	m_pState;


public:
	Android(android_app* pState, const unsigned int priority);
	virtual ~Android();

	android_app*	GetAppState() { return m_pState; }

	virtual bool	Start();
	virtual void 	OnSuspend();
	virtual void 	Update();
	virtual void 	OnResume();
	virtual void 	Stop();

	static void ClearClosing()					{ m_bClosing = false; }
	static bool IsClosing()						{ return m_bClosing; }
	static void SetPaused(const bool paused)	{ m_bPaused = paused; }
	static bool IsPaused()		 				{ return m_bPaused; }

public:
	virtual std::string getName()		{ return "Android"; }

public:
	static void android_handle_cmd(struct android_app* app, int32_t cmd);
	static boost::signals2::signal<void()> sigInit;
	static boost::signals2::signal<void()> sigDestroy;
	static boost::signals2::signal<void()> sigTermWindow;

	static int android_handle_input(struct android_app* app, AInputEvent* event);
	static boost::signals2::signal<void()> sigTouch;
};


#endif // ANDROID_H_
