#pragma once

#include "Engine/Events/Event.h"

namespace Engine
{

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent(void) = default;

		EVENT_CLASS_TYPE(WindowClose)
	};

}