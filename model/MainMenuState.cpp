#include "MainMenuState.hpp"

MainMenuState::MainMenuState(int selectedIndex)
    : _selectedIndex(selectedIndex)
{
}

int MainMenuState::selectedIndex()
{
    return _selectedIndex;
}

void MainMenuState::selectIndex(int index)
{
    _selectedIndex = index;
}
