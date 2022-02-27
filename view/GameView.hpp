#pragma once

#include <vector>
#include <Model.h>
#include <Animation.hpp>
#include <FloorView.h>
#include <PauseMenuView.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "View.hpp"
#include <Portal.hpp>
#include <Medikit.hpp>

class GameView : public View {
    private:
    std::vector<sf::Texture> _textures;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::IntRect> _rects;
    std::vector<Animation> _animations;

    sf::RenderWindow *_renderWindow;
    Model& model;
    FloorView floorView;
    PauseMenuView &pauseMenuView;

    void adjustSprite(int spriteId, Entity* entity, bool upworld);

    public:
    GameView(sf::RenderWindow *renderWindow, Model& model, PauseMenuView &pauseMenuView);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;

    private:
    sf::Vector2f convertWorldCoordinates(WorldCoordinates coords);
    void drawPortal(Portal *portal, double time);
    void drawMedikit(Medikit *medikit, double time);
    bool loadAnimation(const std::string &filename, const unsigned int spriteWidthPx, const unsigned int spriteHeightPx, const int frame_count);
};
