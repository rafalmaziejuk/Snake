#pragma once

namespace Engine
{

	class ImGuiRenderer
	{
	public:
		static void init(void);
		static void shutdown(void);

		static void begin(void);
		static void end(void);
	};

}