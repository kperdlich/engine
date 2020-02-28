workspace "Engine"
architecture "x86_64"
startproject "Engine"
configurations
	{
		"Windows_Debug",
		"Windows_Release",
		"Wii"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}
	
project "Engine"
	location "Engine"
	kind "StaticLib"
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
	filter "configurations:Windows_Debug"
		defines {"WINDOWS", "RELEASE"}
		runtime "Debug"
		symbols "on"
		files 
		{
			"%{prj.name}/src/windows/**.h",
			"%{prj.name}/src/windows/**.cpp",
			"%{prj.name}/src/windows/**.cc"
		}
		includedirs
		{
			"%{prj.name}/src/windows",
			"%{prj.name}/src/windows/third-party",
			"%{prj.name}/src/windows/glfw/include"			
		}
	filter "configurations:Windows_Release"
		defines {"WINDOWS", "RELEASE"}
		runtime "Release"
		optimize "on"		
		files 
		{
			"%{prj.name}/src/windows/**.h",
			"%{prj.name}/src/windows/**.cpp",
			"%{prj.name}/src/windows/**.cc"
		}
		includedirs
		{
			"%{prj.name}/src/windows",
			"%{prj.name}/src/windows/third-party",
			"%{prj.name}/src/windows/glfw/include"			
		}
		
	filter "configurations:Wii"
		defines {"WII", "RELEASE"}
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
			"%{prj.name}/src/wii/third-party"			
		}
