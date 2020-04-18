#pragma once
#include "renderer.h"
#include "input_manager.h"
#include "resource_manager.h"

struct EngineEnvironment
{
	std::shared_ptr<renderer::Renderer> Renderer;
	std::shared_ptr<input::InputManager> Input;
	std::shared_ptr<core::ResourceManager> ResourceManager;
};

extern const std::unique_ptr<EngineEnvironment> gEnv;