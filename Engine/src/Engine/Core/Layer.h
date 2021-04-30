#pragma once

namespace Engine
{
	class Event;

	class Layer
	{
	public:
		virtual ~Layer(void) = default;

		virtual void on_attach(void) {  }
		virtual void on_detach(void) {  }
		virtual void on_event(Event &e) {  }
		virtual void on_update(float timestep) {  }
		virtual void on_render(void) {  }
		virtual void on_imgui_render(void) {  }
	};

}