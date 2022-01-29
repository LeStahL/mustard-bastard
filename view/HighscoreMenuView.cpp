#include "HighscoreMenuView.hpp"
#include <SFML/Graphics.hpp>

#include <iostream>

HighscoreMenuView::HighscoreMenuView(sf::RenderWindow *renderWindow, MenuState *menuState, HighscoreList *highscoreList)
    : _menuState(menuState)
    , _renderWindow(renderWindow)
    , _highscoreList(highscoreList)
{
    _textures.resize(1);
    _textures[0].loadFromFile("assets/highscore_bg.png");

    _sprites.resize(1);
    _sprites[0].setTexture(_textures[0]);

    _font.loadFromFile("assets/FiraCode-Regular.ttf");
}

bool HighscoreMenuView::draw(double time)
{
    _renderWindow->draw(_sprites[0]);

    for(int i=0; i<HighscoreList::nEntries; ++i)
    {
        HighscoreListEntry entry = _highscoreList->entry(i);

        sf::Text text;
        text.setFont(_font);
        text.setString(std::to_string(i+1) + ". " + std::to_string(entry.score()) + " - " + entry.name());
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setPosition(sf::Vector2f(150,200+25*i));
        _renderWindow->draw(text);
    }

    return true;
}

bool HighscoreMenuView::setUp()
{
    return true;
}

bool HighscoreMenuView::tearDown()
{
    return true;
}
