#pragma once

#include <memory>
#include <mutex>
#include <iostream>
#include <cstdint>
#include "core.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using Mutex = std::mutex;
using lock_guard = std::lock_guard<std::mutex>;