#pragma once

#include "../Core/System.h"

namespace ew {
	class InputSystem : public System {
	public:

		enum class ButtonState {
			IDLE,
			PRESSED,
			HELD,
			RELEASED
		};

		virtual bool startup() override;
		virtual void shutdown() override;
		virtual void update() override;

		ButtonState getButtonState(int id);
		bool getButtonDown(int id);
		bool getPreviousButton(int id);


	protected:
		Uint8* keyState;
		Uint8* prevKeyState;
		int numKeys;


	};
}