#include <jni.h>
#include <android_native_app_glue.h>
#include <Util/Logger.hpp>
#include "Kernel.h"
#include "Timer.h"
#include "Android.h"
#include "Renderer.h"
#include "Chapter5Task.h"

void android_main(android_app* pState)
{

	Util::File::SetAssetManager(pState->activity->assetManager);

	Kernel kernel;

	Android androidTask(pState, Task::PLATFORM_PRIORITY);
	Timer timerTask(Task::TIMER_PRIORITY);
	Renderer rendererTask(pState, Task::RENDER_PRIORITY);
	pState->userData = static_cast<void*>(&rendererTask);

	Chapter5Task mainTask(&rendererTask, Task::GAME_PRIORITY);

	kernel.AddTask(&androidTask);
	kernel.AddTask(&timerTask);
	kernel.AddTask(&rendererTask);
	kernel.AddTask(&mainTask);

	kernel.Execute();
}

void _android_main(android_app* pState)
{
	app_dummy();

	DLOG() << "hello";
	DLOG() << "world";
	DLOG() << "hello" << "world";

	int events;
	android_poll_source* pSource;

	while(true)
	{
		int ident = ALooper_pollAll(0, 0, &events, (void**)&pSource);
		if (ident >= 0)
		{
			if (pSource)
			{
				pSource->process(pState, pSource);
			}

			if (pState->destroyRequested)
			{
				DLOG() << "destroy";
				break;
			}
		}
	}
}
