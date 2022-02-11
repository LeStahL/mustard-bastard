#pragma once

#include <vector>
#include <Model.h>
#include <Animation.hpp>
#include <FloorView.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "View.hpp"

class GameView : public View {
    private:
    std::vector<sf::Texture> _textures;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::IntRect> _rects;
    std::vector<Animation> _animations;

    sf::RenderWindow *_renderWindow;
    Model& model;
    FloorView floorView;

    void adjustSprite(int spriteId, Entity* entity, bool upworld);

    public:
    GameView(sf::RenderWindow *renderWindow, Model& model);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;

    private:
    sf::Vector2f convertWorldPosition(WorldPosition position);
    bool loadAnimation(const std::string &filename, const unsigned int spriteWidthPx, const unsigned int spriteHeightPx, const int frame_count);
};