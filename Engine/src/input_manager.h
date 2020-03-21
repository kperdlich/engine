#pragma once
#include <cstdint>
#include <unordered_map>
#include <memory>

namespace input {

	constexpr int32_t KEYCODE_UP = 1;
	constexpr int32_t KEYCODE_LEFT = 2;
	constexpr int32_t KEYCODE_DOWN = 3;
	constexpr int32_t KEYCODE_RIGHT = 4;
	constexpr int32_t KEYCODE_ESC = 5;

	constexpr int32_t KEYCODE_MOUSE_1 = 400;
	constexpr int32_t KEYCODE_MOUSE_2 = 401;
	constexpr int32_t KEYCODE_MOUSE_3 = 402;
	constexpr int32_t KEYCODE_MOUSE_4 = 403;
	constexpr int32_t KEYCODE_MOUSE_5 = 404;
	
	enum class ButtonState : int8_t
	{
		Released = 0,
		Pressed = 1,
		Repeat = 2,
	};

	class InputManager {
	public:		
		InputManager();
		~InputManager() = default;
		InputManager(const InputManager&) = delete;
		InputManager(InputManager&&) = delete;
		InputManager& operator=(const InputManager&) = delete;
		InputManager& operator=(InputManager&&) = delete;		
		float GetInputValue(int32_t keycode);
		ButtonState GetState(int32_t keycode);
	private:
		std::unordered_map<int32_t, int32_t> mKeycodeMap;
	};
}