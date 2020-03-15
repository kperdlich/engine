#pragma once

#include <memory>
#include <mutex>
#include <iostream>
#include <cstdint>
#include "core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include "windows/opengl_vertexbuffer.h"

using Mutex = std::mutex;
using lock_guard = std::lock_guard<std::mutex>;