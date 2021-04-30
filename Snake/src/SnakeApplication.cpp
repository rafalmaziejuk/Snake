#include <Engine.h>
#include <Engine/Core/main.h>

#include "GameLayer.h"

namespace Engine
{

	class SnakeApplication : public Application
	{
	public:
		SnakeApplication(void) :
			Application("Snake")
		{
			push_layer(new GameLayer());
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