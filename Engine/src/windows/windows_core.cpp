#include "core.h"
#include "windows_defines.h"

void core::Assert(const char* expression, const char* file, int32_t line, const char* format, ...)
{
	std::cout << "Assertion failed: " << expression << " file: " << file << " Line: " << line;
	__debugbreak();
}
