#pragma once

#include <mutex>
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using Mutex = std::mutex;
using lock_guard = std::lock_guard<std::mutex>;