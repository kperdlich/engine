#include "input_manager.h"
#include "platform.h"

input::InputManager::InputManager()
{
	WPAD_Init();
	WPAD_SetVRes(WPAD_CHAN_0, gEnv->Renderer->GetWidth(), gEnv->Renderer->GetHeight());
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
	WPAD_ScanPads();

	mKeycodeMap[KEYCODE_UP] = WPAD_BUTTON_UP;
	mKeycodeMap[KEYCODE_LEFT] = WPAD_BUTTON_LEFT;
	mKeycodeMap[KEYCODE_DOWN] = WPAD_BUTTON_DOWN;
	mKeycodeMap[KEYCODE_RIGHT] = WPAD_BUTTON_RIGHT;
	mKeycodeMap[KEYCODE_ESC] = WPAD_BUTTON_HOME;

	mKeycodeMap[KEYCODE_MOUSE_1] = WPAD_BUTTON_A;
	mKeycodeMap[KEYCODE_MOUSE_2] = WPAD_BUTTON_B;	
}

float input::InputManager::GetInputValue(int32_t keycode)
{
	ASSERT(mKeycodeMap.find(keycode) != mKeycodeMap.end());	
	uint32_t wiipadKeycode = mKeycodeMap.at(keycode);	

	WPAD_ScanPads();
	uint32_t buttonDown = WPAD_ButtonsDown(WPAD_CHAN_0);
	uint32_t buttonHeld = WPAD_ButtonsHeld(WPAD_CHAN_0);
	uint32_t buttonUp = WPAD_ButtonsUp(WPAD_CHAN_0);

	if ((buttonDown & wiipadKeycode) || (buttonHeld & wiipadKeycode))
	{
		return 1.0f;
	}		
	return 0.0f;
}

input::ButtonState input::InputManager::GetState(int32_t keycode)
{
	const float value = GetInputValue(keycode);
	return static_cast<input::ButtonState>(static_cast<int8_t>(value));
}