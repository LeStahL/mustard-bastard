#pragma once

class MainMenuState
{
    int _selectedIndex;
    
    public:
    MainMenuState(int selectedIndex = 0);

    int selectedIndex();
    void selectIndex(int index);
};
