#include "MenuState.h"
#include <iostream>

MenuState::MenuState(StateManager &stateManager, Context context) :
	State(stateManager, context)
{

}

MenuState::~MenuState(void)
{

}

void MenuState::draw(void) const
{

}

bool MenuState::update(float timestep)
{
	return true;
}

bool MenuState::handle_input(void)
{
	return true;
}