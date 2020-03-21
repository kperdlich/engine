#include "input_manager.h"
#include "platform.h"


input::InputManager::InputManager()
{
	mKeycodeMap[KEYCODE_UP] = GLFW_KEY_UP;
	mKeycodeMap[KEYCODE_LEFT] = GLFW_KEY_LEFT;
	mKeycodeMap[KEYCODE_DOWN] = GLFW_KEY_DOWN;
	mKeycodeMap[KEYCODE_RIGHT] = GLFW_KEY_RIGHT;
	mKeycodeMap[KEYCODE_ESC] = GLFW_KEY_ESCAPE;

	mKeycodeMap[KEYCODE_MOUSE_1] = GLFW_MOUSE_BUTTON_1;
	mKeycodeMap[KEYCODE_MOUSE_2] = GLFW_MOUSE_BUTTON_2;
	mKeycodeMap[KEYCODE_MOUSE_3] = GLFW_MOUSE_BUTTON_3;
	mKeycodeMap[KEYCODE_MOUSE_4] = GLFW_MOUSE_BUTTON_4;
	mKeycodeMap[KEYCODE_MOUSE_5] = GLFW_MOUSE_BUTTON_5;
}

float input::InputManager::GetInputValue(int32_t keycode)
{
	ASSERT(mKeycodeMap.find(keycode) != mKeycodeMap.end());
	GLFWwindow* window = glfwGetCurrentContext();
	const int32_t glfwKeyCode = mKeycodeMap.at(keycode);
	if (keycode >= KEYCODE_MOUSE_1) 
	{
		return static_cast<float>(glfwGetMouseButton(window, glfwKeyCode));
	}
	else 
	{				
		return static_cast<float>(glfwGetKey(window, glfwKeyCode));
	}	
}

input::ButtonState input::InputManager::GetState(int32_t keycode)
{
	const float value = GetInputValue(keycode);
	return static_cast<input::ButtonState>(static_cast<int8_t>(value));
}
