#pragma once

#include "Event.h"

namespace Gaea {
	class GAEA_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y)
			: _MouseX(x), _MouseY(y) {}
		inline float GetX() { return _MouseX; }
		inline float GetY() { return _MouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseMovedEvent: " << _MouseX << ", " << _MouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float _MouseX, _MouseY;
	};

	class GAEA_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(float XOffset, float YOffset)
			: _XOffset(XOffset), _YOffset(YOffset) {}

		inline float GetXOffset() const { return _XOffset; }
		inline float GetYOffset() const { return _YOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float _XOffset, _YOffset;
	};

	class GAEA_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const{ return _Button; }

			EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	protected:
		MouseButtonEvent(int button)
			: _Button(button) {}

		int _Button;
	};

	class GAEA_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << _Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonPressed)

	};

	class GAEA_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << _Button;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseButtonReleased)

	};
}