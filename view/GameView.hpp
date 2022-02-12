#pragma once

#include <vector>
#include <Model.h>
#include <Animation.hpp>
#include <FloorView.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "View.hpp"

class Entity;

enum AnimationType {
    BastardStanding,
    BastardWalking,
    BastardAttacking,
    ZombieWalking,
    CatWalking,
    IcebergSliding,
    FairyFlying
};

typedef struct {
    std::string assetPath;
    unsigned int width;
    unsigned int height;
    unsigned int frameCount;
} AnimationAssetInformation;

typedef struct {
    sf::Texture *texture;
    sf::Sprite *sprite;
} AnimationData;

class GameView : public View {
    private:
    static const std::map<AnimationType, AnimationAssetInformation> assetInformations;
    std::map<AnimationType, AnimationData> _animationData;
    std::map<Entity *, Animation> _animations;

    sf::RenderWindow *_renderWindow;
    Model& model;
    FloorView floorView;

    void adjustSprite(int spriteId, Entity* entity, bool upworld);

    public:
    GameView(sf::RenderWindow *renderWindow, Model& model);

    bool draw(double time) override;
    bool setUp() override;
    bool tearDown() override;

    bool registerAnimation(Entity *entity, AnimationType type, double frameDelay, double initialTimeOffset);

    private:
    sf::Vector2f convertWorldCoordinates(WorldCoordinates coords);
    bool loadAnimationData(AnimationType type, AnimationAssetInformation information);
};