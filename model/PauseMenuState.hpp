#pragma once

class PauseMenuState
{
    int _selectedIndex;
    
    public:
    PauseMenuState(int selectedIndex = 0);

    int selectedIndex();
    void selectIndex(int index);
};
