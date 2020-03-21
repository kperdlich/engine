#pragma once
#include "renderer.h"
#include "input_manager.h"

struct EngineEnvironment
{
	std::shared_ptr<renderer::Renderer> Renderer;
	std::shared_ptr<input::InputManager> Input;
};

extern const std::unique_ptr<EngineEnvironment> gEnv;