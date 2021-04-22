#include <Engine.h>
#include <Engine/Core/main.h>

namespace Engine
{

	class SnakeApplication : public Application
	{
	public:
		SnakeApplication(void) :
			Application("Snake")
		{

		}

		virtual ~SnakeApplication(void)
		{

		}
	};

	Application * create_application(void)
	{
		return new SnakeApplication();
	}

}