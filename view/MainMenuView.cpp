#include "MainMenuView.hpp"
#include <SFML/Graphics.hpp>

MainMenuView::MainMenuView(sf::RenderWindow *renderWindow, MenuState *menuState, MainMenuState *mainMenuState)
    : _menuState(menuState)
    , _mainMenuState(mainMenuState)
    , _renderWindow(renderWindow)
{
    _textures.resize(2);
    _textures[0].loadFromFile("assets/mainscreen.png");
    _textures[1].loadFromFile("assets/mainscreen_highlights.png");

    _sprites.resize(3);
    for(int i=0; i<2; ++i)
        _sprites[i].setTexture(_textures[i]);

    _rects.resize(4);
    for(int i=0; i<4; ++i)
    {
        _rects[i].left = i*960;
        _rects[i].top = 0;
        _rects[i].width = 960;
        _rects[i].height = 540;
    }
}

bool MainMenuView::draw(double time)
{
    _sprites[1].setTextureRect(_rects[_mainMenuState->selectedIndex()]);
    
    for(int i=0; i<_sprites.size(); ++i)
        _renderWindow->draw(_sprites[i]);

    return true;
}

bool MainMenuView::setUp()
{
    _mainMenuState->selectIndex(0);

    return true;
}

bool MainMenuView::tearDown()
{
    return true;
}
