#pragma once

#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <View.hpp>
#include <NeedsEnemyNotifications.hpp>

#include <Model.h>
#include <Animation.hpp>
#include <FloorView.h>
#include <Portal.hpp>
#include <Medikit.hpp>

class GameView : public View, public NeedsEnemyNotifications {
    private:
    std::vector<sf::Texture> _textures;
    std::vector<sf::Sprite> _sprites;
    std::vector<sf::IntRect> _rects;
    std::vector<Animation> _animations;

    sf::RenderWindow *_renderWindow;
    Model *model;
    FloorView floorView;;
    float attackTime;
    bool weaponUp;

    std::vector<float> enemyLocalPhase;

    void adjustSprite(int spriteId, Entity* entity, bool upworld);

    public:
    GameView(sf::RenderWindow *renderWindow, Model *model);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;

    // NeedsEnemyNotifications implemetations
    void enemyAdded() override;
    void enemyRemoved(int index) override;

    private:
    sf::Vector2f convertWorldCoordinates(WorldCoordinates coords);
    void drawPortal(Portal *portal, double time);
    void drawMedikit(Medikit *medikit, double time);
    void drawWeapon(Weapon *weapon, double time);
    bool loadAnimation(const std::string &filename, const unsigned int spriteWidthPx, const unsigned int spriteHeightPx, const int frameCount, const float frameDelay);
};
