#pragma once

#include "Event.h"
#include <sstream>

namespace Gaea {
	class GAEA_API KeyEvent : public Event {
	public: 
		inline int GetKeyCode() const { return _KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int keyCode) 
			: _KeyCode(keyCode) {}

		int _KeyCode;
	};

	class GAEA_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int keyCode, int repeatCount)
			: KeyEvent(keyCode), _RepeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return _RepeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedEvent: " << _KeyCode << " (" << _RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int _RepeatCount;
	};

	class GAEA_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent (int keyCode)
			: KeyEvent(keyCode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << _KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	};
}