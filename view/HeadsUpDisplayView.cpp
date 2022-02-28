#include "HeadsUpDisplayView.hpp"

#include "const.h"

#include <iostream>

HeadsUpDisplayView::HeadsUpDisplayView(sf::RenderWindow *renderWindow)
    : _renderWindow(renderWindow)
    , _player1(nullptr)
    , _player2(nullptr)
{
    auto _ = _font.loadFromFile("assets/FiraCode-Regular.ttf");
}

void HeadsUpDisplayView::setPlayer1(Player *player) {
    _player1 = player;
}

void HeadsUpDisplayView::setPlayer2(Player *player) {
    _player2 = player;
}

void HeadsUpDisplayView::drawPlayerHUD(Player *player, HUDSide where)
{
    double xdelta = 0.;
    if(where == HUDSide::Right) xdelta += WIDTH - 440;

    // Player name
    sf::Text nametext;
    nametext.setFont(_font);
    nametext.setString(player->name);
    nametext.setCharacterSize(24);
    nametext.setFillColor(sf::Color::White);
    nametext.setPosition(sf::Vector2f(20+xdelta,GAME_HEIGHT));
    _renderWindow->draw(nametext);

    // Health bar
    sf::RectangleShape healthBarOutline;
    healthBarOutline.setSize(sf::Vector2f(100, 25));
    healthBarOutline.setOutlineColor(sf::Color::White);
    healthBarOutline.setFillColor(sf::Color::Transparent);
    healthBarOutline.setOutlineThickness(2);
    healthBarOutline.setPosition(sf::Vector2f(20+xdelta, GAME_HEIGHT + 30));
    _renderWindow->draw(healthBarOutline);

    sf::RectangleShape healthBarContent;
    healthBarOutline.setSize(sf::Vector2f(94*player->health, 19));
    healthBarOutline.setFillColor(sf::Color::White);
    healthBarOutline.setPosition(sf::Vector2f(23+xdelta, GAME_HEIGHT + 33));
    _renderWindow->draw(healthBarOutline);

    // Power
    sf::Text powerText;
    powerText.setFont(_font);
    powerText.setString(std::string("Power: ") + std::to_string(player->power));
    powerText.setCharacterSize(24);
    powerText.setFillColor(sf::Color::White);
    powerText.setPosition(sf::Vector2f(140+xdelta,GAME_HEIGHT));
    _renderWindow->draw(powerText);

    // Points
    sf::Text pointsText;
    pointsText.setFont(_font);
    pointsText.setString(std::string("Points: ") + std::to_string(player->points));
    pointsText.setCharacterSize(24);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition(sf::Vector2f(140+xdelta,GAME_HEIGHT+28));
    _renderWindow->draw(pointsText);

    // Cooldown
    sf::Text cooldownText;
    cooldownText.setFont(_font);
    cooldownText.setString(std::string("Cooldown: ") + std::to_string(player->move_z_cooldown));
    cooldownText.setCharacterSize(24);
    cooldownText.setFillColor(sf::Color::White);
    cooldownText.setPosition(sf::Vector2f(140+xdelta,GAME_HEIGHT+56));
    _renderWindow->draw(cooldownText);
}

bool HeadsUpDisplayView::draw(double time)
{
    // Player 1 (TODO: refactor into smart functions)
    if(_player1 != nullptr) drawPlayerHUD(_player1, HUDSide::Left);
    if(_player2 != nullptr) drawPlayerHUD(_player2, HUDSide::Right);

    return true;
}

bool HeadsUpDisplayView::setUp()
{
    return true;
}

bool HeadsUpDisplayView::tearDown()
{
    return true;
}
