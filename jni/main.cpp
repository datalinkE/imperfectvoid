#include <jni.h>
#include <android_native_app_glue.h>
#include <android/log.h>

void android_main(android_app* pState)
{
	app_dummy();
	__android_log_print(ANDROID_LOG_DEBUG, "IMP", "Hello world\n");

	int events;
	struct android_poll_source* pSource;
	int ident = ALooper_pollAll(0, 0, &events, (void**)&pSource);
	if (ident >= 0)
	{
		if (pSource)
		{
			pSource->process(pState, pSource);
		}

		if (pState->destroyRequested)
		{
			__android_log_print(ANDROID_LOG_DEBUG, "IMP", "Destroy\n");
		}
	}

}
