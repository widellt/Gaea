#pragma once
#include "Gaea/Input.h"

namespace Gaea {
	class WindowsInput : public Input {
	protected:
		// Keys
		virtual bool IsKeyPressedImpl(int keycode) override;

		// Mouse
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePosImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}
