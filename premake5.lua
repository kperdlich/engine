workspace "Engine"
	architecture "x86_64"
	startproject "Engine"
	configurations
	{
		"Windows",		
		"Wii"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}	
	
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	include "Engine/third-party/glfw"
	include "Engine/third-party/glad"
	include "Engine/third-party/imgui"

	
	project "Engine"
		location "Engine"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "on"
		files
		{
			"%{prj.name}/src/*.h",
			"%{prj.name}/src/*.cpp",
			"%{prj.name}/src/third-party/**.h",
			"%{prj.name}/src/third-party/**.cpp",
			"%{prj.name}/src/third-party/**.cc"
		}	
		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/src/third-party",
		}
		links 
		{
			"GLAD",
			"GLFW",
			"IMGUI",
			"opengl32.lib"
		}
		filter "configurations:Windows"		
			runtime "Debug"
			symbols "on"
			files 
			{
				"%{prj.name}/src/windows/**.h",
				"%{prj.name}/src/windows/**.cpp",
				"%{prj.name}/third-party/glm/glm/**.hpp",
				"%{prj.name}/third-party/glm/glm/**.inl",
			}
			includedirs
			{
				"%{prj.name}/src/windows",
				"%{prj.name}/src/windows/third-party",
				"%{prj.name}/third-party/glfw/include",
				"%{prj.name}/third-party/glad/include",
				"%{prj.name}/third-party/imgui",
				"%{prj.name}/third-party/glm"		
			}			
			defines
			{		
				"WINDOWS",
				"GLFW_INCLUDE_NONE"
			}
			
		filter "configurations:Wii"
			defines "WII"
			runtime "Release"
			optimize "on"
			files 
			{
				"%{prj.name}/src/wii/**.h",
				"%{prj.name}/src/wii/**.cpp",
				"%{prj.name}/src/wii/**.cc"
			}		
			includedirs
			{
				"%{prj.name}/src/wii",
				"%{prj.name}/src/wii/third-party",
				"F:/devkitPro/libogc/include",
				"F:/devkitPro/devkitPPC/powerpc-eabi/include",
				"F:/devkitPro/devkitPPC/lib/gcc/powerpc-eabi/6.3.0/include"				
			}
