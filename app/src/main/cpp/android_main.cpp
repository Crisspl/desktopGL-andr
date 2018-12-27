
extern "C" {
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <jni.h>
#include <errno.h>
#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>
#include <unistd.h>
#include <stdlib.h>
}

extern "C" {
    void android_main(struct android_app* state);
};

void android_main(struct android_app *app) {
    if(eglBindAPI(EGL_OPENGL_API))
    {
        EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
        eglInitialize(display, NULL, NULL);
        const EGLint configAttrs[] =
                {
                        EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                        EGL_RENDERABLE_TYPE, EGL_OPENGL_BIT,
                        EGL_RED_SIZE, 8,
                        EGL_GREEN_SIZE, 8,
                        EGL_BLUE_SIZE, 8,
                        EGL_DEPTH_SIZE, 24,
                        EGL_NONE
                };
        EGLConfig config;
        EGLint    numConfigs = 0;
        eglChooseConfig(display, configAttrs, &config, 1, &numConfigs);
        EGLint ctxAttrs[] =
                {
                        EGL_NONE
                };
        EGLContext ctx = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttrs);
        if (ctx == EGL_NO_CONTEXT)
            __android_log_print(ANDROID_LOG_DEBUG, "debug", "#1 Failed to create desktop GL ctx!");
    }
    else
    {
        __android_log_print(ANDROID_LOG_DEBUG, "debug", "#2 Failed to create desktop GL ctx!");
    }
}

