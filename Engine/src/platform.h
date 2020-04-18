#pragma once

#ifdef WINDOWS	
	#include "windows/windows_defines.h"
	#include "windows/opengl_shader.h"
    #include "windows/opengl_vertexbuffer.h"
#else
	#include "wii/wii_defines.h"
	#include "wii/wii_shader.h"
    #include "wii/wii_vertexbuffer.h"
	#include "wii/lockguard.h"
	#include "wii/mutex.h"
#endif

#include "third-party/fastdelegate.h"
#include "third-party/fastdelegatebind.h"
#include "third-party/tiny_obj_loader.h"
#include "input_manager.h"
#include "resource_manager.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexformat.h"
#include "image2d.h"
#include "texture2d.h"
#include "renderer.h"
#include "camera.h"
#include "environment.h"
