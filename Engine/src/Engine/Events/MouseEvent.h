#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Core/MouseCodes.h"

namespace Engine
{

	class MouseMovedEvent : public Event
	{
	private:
		float m_x, m_y;

	public:
		MouseMovedEvent(float x, float y) :
			m_x(x), m_y(y)
		{
			
		}

		float get_x(void) const { return m_x; }
		float get_y(void) const { return m_y; }

		EVENT_CLASS_TYPE(MouseMoved)
	};

	class MouseButtonEvent : public Event
	{
	protected:
		MouseButtonEvent(MouseCode button) :
			m_button(button)
		{
			
		}

		MouseCode m_button;

	public:
		inline MouseCode get_mouse_button(void) const { return m_button; }
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button) :
			MouseButtonEvent(button)
		{
			
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button) :
			MouseButtonEvent(button)
		{
			
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}