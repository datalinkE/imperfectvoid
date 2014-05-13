LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE     := imperfect-void
LOCAL_SRC_FILES  := main.cpp \
				   TasksLoop.cpp \
				   Android.cpp \
				   Timer.cpp \
				   Renderer.cpp \
				   Chapter5Task.cpp	\
				   Util/File.cpp \
				   Util/TGAFile.cpp \
				   Renderable/Geometry/Geometry.cpp \
				   Renderable/Textures/Texture.cpp \
				   Renderable/Shaders/ShaderProgram.cpp \
				   Renderable/Shaders/GeometryShaderProgram.cpp \
				   Renderable/Shaders/TextureShaderProgram.cpp \
				   Renderable/Transform2D.cpp
				   
				   
BOOST_INCLUDES := $(LOCAL_PATH)/../../boost_1_55_0
GLM_INCLUDES := $(LOCAL_PATH)/../../glm-0.9.5.3
LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_C_INCLUDES += $(BOOST_INCLUDES)
LOCAL_C_INCLUDES += $(GLM_INCLUDES)
LOCAL_CPP_FEATURES += exceptions
LOCAL_LDLIBS := -llog -landroid -lEGL -lGLESv2
LOCAL_STATIC_LIBRARIES := android_native_app_glue

include $(BUILD_SHARED_LIBRARY)
$(call import-module, android/native_app_glue)
