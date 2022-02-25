#include "PauseMenuState.hpp"

PauseMenuState::PauseMenuState(int selectedIndex)
    : _selectedIndex(selectedIndex)
{
}

int PauseMenuState::selectedIndex()
{
    return _selectedIndex;
}

void PauseMenuState::selectIndex(int index)
{
    _selectedIndex = index;
}
