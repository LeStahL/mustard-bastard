#pragma once

class MenuState {
    public:
    enum MenuType {
        MainMenu,
        Game,
        PauseMenu,
        SettingsMenu,
        HighScoreMenu,
        Exit
    };

    MenuState();
    MenuType currentType();
    void setType(MenuType type);

    private:
    MenuType _type;
};
