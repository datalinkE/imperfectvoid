LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := imperfect-void
LOCAL_SRC_FILES  := main.cpp \
				   Kernel.cpp \
				   Android.cpp \
				   Timer.cpp \
				   Renderer.cpp \
				   Renderable/Geometry/Geometry.cpp \
				   Renderable/Shaders/BasicShader.cpp \
				   Renderable/Shaders/Shader.cpp \
				   Renderable/Shaders/TextureShader.cpp \
				   Renderable/Textures/Texture.cpp \
				   Util/File.cpp \
				   Util/TGAFile.cpp \
				   Chapter5Task.cpp
				   
BOOST_INCLUDES := $(LOCAL_PATH)/../../boost_1_55_0
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(BOOST_INCLUDES)
LOCAL_CPP_FEATURES += exceptions
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)
$(call import-module, android/native_app_glue)
