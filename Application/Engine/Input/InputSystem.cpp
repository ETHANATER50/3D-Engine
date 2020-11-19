#include "pch.h"
#include "InputSystem.h"

namespace ew {
	bool InputSystem::startup() {
		const Uint8* retrieved = SDL_GetKeyboardState(&numKeys);
		keyState = new Uint8[numKeys];
		prevKeyState = new Uint8[numKeys];

		memcpy(keyState, retrieved, numKeys);
		memcpy(prevKeyState, keyState, numKeys);

		return true;
	}

	void InputSystem::shutdown() {
		delete[] keyState;
		delete[] prevKeyState;

	}

	void InputSystem::update() {
		memcpy(prevKeyState, keyState, numKeys);

		const Uint8* retrieved = SDL_GetKeyboardState(nullptr);
		memcpy(keyState, retrieved, numKeys);
	}

	InputSystem::ButtonState InputSystem::getButtonState(int id) {
		ButtonState state = ButtonState::IDLE;
		bool buttonDown = getButtonDown(id);
		bool prevButtonDown = getPreviousButton(id);

		if (buttonDown) {
			state = (prevButtonDown) ? ButtonState::HELD : ButtonState::PRESSED;
		}
		else {
			state = (prevButtonDown) ? ButtonState::RELEASED : ButtonState::IDLE;
		}

		return state;
	}

	bool InputSystem::getButtonDown(int id) {
		return keyState[id];
	}

	bool InputSystem::getPreviousButton(int id) {
		return prevKeyState[id];
	}

}

