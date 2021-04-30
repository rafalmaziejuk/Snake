#pragma once

#include "Engine/Core/KeyCodes.h"
#include "Engine/Core/MouseCodes.h"

#include <glm/vec2.hpp>

namespace Engine
{

	class Input
	{
	public:
		static bool is_key_pressed(KeyCode key);
		static bool is_mouse_button_pressed(MouseCode button);
		static glm::vec2 get_mouse_position(void);
	};

}