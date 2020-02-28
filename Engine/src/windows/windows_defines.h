#pragma once

#include <mutex>

using Mutex = std::mutex;
using lock_guard = std::lock_guard<std::mutex>;