#pragma once

#include "third-party/fastdelegate.h"
#include "third-party/fastdelegatebind.h"
#include "third-party/tiny_obj_loader.h"
#include "renderer.h"
#include "camera.h"

#ifdef WINDOWS
	#include "windows_defines.h"
#else
	#include "wii/wii_defines.h"
	#include "wii/lockguard.h"
	#include "wii/mutex.h"
#endif