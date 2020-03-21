#include "core.h"
#include "wii_defines.h"
#include "renderer.h"
#include "wii_renderdata.h"
#include <stdarg.h>

void core::Assert(const char* expression, const char* file, int32_t line, const char* format, ...)
{    
    if (!gEnv->Renderer)
    {
        exit(0);
    }
    renderer::RenderData* renderData = gEnv->Renderer->GetRenderData();
    if (!renderData)
    {
        exit(0);
    }

	gEnv->Renderer->DisplayBuffer();
    void* pFrameBuffer = renderData->mFrameBuffers[renderData->mFrameBufferIndex];
    GXRModeObj* pRMode = renderData->mRmode;

    console_init(pFrameBuffer, 20, 20, pRMode->fbWidth, pRMode->xfbHeight,
        pRMode->fbWidth * VI_DISPLAY_PIX_SZ);

    WPAD_Init();
    WPAD_SetVRes(WPAD_CHAN_0, pRMode->fbWidth, pRMode->xfbHeight);

    printf("\x1b[7;0H");
    printf("Assertion failed:\nFile: %s,\n Line %d\nExpression: %s\n\n", file, line, expression);

    if (format)
    {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
        printf("\n");
    }

    printf("Press 'A' to exit.");

    do
    {
        WPAD_ScanPads();
    }
    while(!(WPAD_ButtonsUp(0) & WPAD_BUTTON_A || WPAD_ButtonsHeld(0) & WPAD_BUTTON_A));
    exit(0);
}
