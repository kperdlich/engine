#include "core.h"
#include "windows_defines.h"
#include "stdarg.h"

void core::Assert(const char* expression, const char* file, int32_t line, const char* format, ...)
{
	std::cout << "Assertion failed: " << expression << " file: " << file << " Line: " << line << " ";

	if (format)
	{
		va_list args;
		va_start(args, format);
		vprintf(format, args);
		va_end(args);
		printf("\n");
	}

	__debugbreak();
}
