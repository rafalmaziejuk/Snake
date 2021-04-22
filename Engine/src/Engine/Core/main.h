#pragma once

extern Engine::Application * Engine::create_application();

int main(void)
{
	auto app = Engine::create_application();
	app->run();
	delete app;

	return 0;
}