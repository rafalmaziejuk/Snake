#include <Engine.h>
#include <Engine/Core/main.h>

#include <imgui.h>

namespace Engine
{

	class SnakeApplication : public Application
	{
	private:


	public:
		SnakeApplication(void) :
			Application("Snake")
		{

		}

		virtual ~SnakeApplication(void)
		{

		}

		virtual void on_update(float timestep) override
		{ 
			
		}

		virtual void on_render(void) override
		{

		}

		virtual void on_imgui_render(void) override
		{

		}
	};

	Application * create_application(void)
	{
		return new SnakeApplication();
	}

}