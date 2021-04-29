#pragma once

#include "Engine/Events/Event.h"
#include "Engine/Core/KeyCodes.h"

namespace Engine
{

	class KeyEvent : public Event
	{
	protected:
		KeyEvent(KeyCode keycode) :
			m_keyCode(keycode)
		{

		}

		KeyCode m_keyCode;

	public:
		inline KeyCode get_key_code(void) const { return m_keyCode; }
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode keycode) :
			KeyEvent(keycode)
		{

		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode keycode) :
			KeyEvent(keycode)
		{

		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

}