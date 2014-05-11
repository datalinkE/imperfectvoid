#include <jni.h>
#include <android_native_app_glue.h>
#include <Util/Logger.hpp>
#include "TasksLoop.h"
#include "Timer.h"
#include "Android.h"
#include "Renderer.h"
#include "Chapter5Task.h"
#include <boost/signals2.hpp>
#include <boost/bind.hpp>

void android_main(android_app* pState)
{

	Util::File::SetAssetManager(pState->activity->assetManager);

	TasksLoop kernel;

	Android eventsTask(pState, Task::PLATFORM_PRIORITY);
	Timer timerTask(Task::TIMER_PRIORITY);
	Renderer rendererTask(pState, Task::RENDER_PRIORITY);
	pState->userData = static_cast<void*>(&rendererTask);

	Android::sigInit.connect(boost::bind(&Renderer::Init, &rendererTask));
	Android::sigDestroy.connect(boost::bind(&Renderer::Destroy, &rendererTask));
	Android::sigTermWindow.connect(boost::bind(&Renderer::Destroy, &rendererTask));

	Chapter5Task logicTask(&rendererTask, Task::GAME_PRIORITY);

	kernel.AddTask(&eventsTask);
	kernel.AddTask(&timerTask);
	kernel.AddTask(&logicTask);
	kernel.AddTask(&rendererTask);

	kernel.Execute();
}

