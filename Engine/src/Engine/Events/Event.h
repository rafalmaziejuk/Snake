#pragma once

namespace Engine
{
	enum class EventType
	{
		None = 0,
		WindowClose,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved
	};

#define EVENT_CLASS_TYPE(type)	static EventType get_static_type(void) { return EventType::type; } \
								virtual EventType get_event_type(void) const override { return get_static_type(); }

	class Event
	{
	public:
		bool handled = false;
		
		virtual ~Event() = default;
		virtual EventType get_event_type() const = 0;
	};

	class EventDispatcher
	{
	private:
		Event &m_event;

	public:
		EventDispatcher(Event &event)
			: m_event(event)
		{

		}

		template<typename T, typename F>
		bool dispatch(const F &func)
		{
			if (m_event.get_event_type() == T::get_static_type())
			{
				m_event.handled |= func(static_cast<T&>(m_event));
				return true;
			}

			return false;
		}
	};

}