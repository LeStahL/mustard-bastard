#include <GameView.hpp>
#include <iostream>
#include "ViewConst.h"
#include <Entity.h>
#include <algorithm>
#include <GameLogic.h>
#include <GameLogicConst.h>
#include <const.h>
#include <cmath>
#include <Portal.hpp>

std::map<int, int> playerStateToSprite = {
    { PlayerState::Standing, Model::GraphicsId::player_standing },
    { PlayerState::Walking, Model::GraphicsId::player_walking },
    { PlayerState::Attacking, Model::GraphicsId::player_attack },
    { PlayerState::Warping, Model::GraphicsId::player_standing }
};

GameView::GameView(sf::RenderWindow *renderWindow, Model& model) :
    _renderWindow(renderWindow),
    model(model),
    floorView(FloorView(_renderWindow)) {
}

sf::Vector2f GameView::convertWorldCoordinates(WorldCoordinates position) {
    sf::Vector2f pixelPos;

    pixelPos.x = position.x;
    pixelPos.y = floorView.getBackgroundBaseLine(position);

    return pixelPos;
}

void GameView::adjustSprite(int spriteId, Entity* entity, bool invertWorld)
{
    // small hack, not pretty - qm: don't get why this was done. I changed it.
    WorldCoordinates pos = entity->coords;
    pos.upWorld ^= invertWorld;

    auto sprite = &(_sprites.at(spriteId));
    sprite->setPosition(convertWorldCoordinates(pos));

    int x_sign = 1;
    if(pos.upWorld) {
        sprite->setRotation(0.0f);
        x_sign = entity->coords.facing_left ? -1 : 1;
    } else {
        sprite->setRotation(180.0f);
        x_sign = entity->coords.facing_left ? 1 : -1;
    }
    sprite->setScale(sf::Vector2f(x_sign, 1));

    // special transformation in case of warping player
    auto player = dynamic_cast<Player*>(entity);
    if (player != nullptr && player->state == PlayerState::Warping) {
        float progress = player->getWarpProgress();
        float x_scale = progress < 0.5
            ? 1. - 2. * progress
            : 2. * (progress - 0.5);
        sprite->scale(sf::Vector2f(x_scale, 1./(x_scale + .01)));
    }
}

auto drawPortal = [](Portal* portal, double y, double time) {
    auto halfwidth = portal->getHalfWidth();
    auto result = sf::CircleShape(halfwidth);
    result.setPosition(sf::Vector2f(
        portal->coords.x - halfwidth,
        y - halfwidth * PORTAL_HEIGHT_RATIO + 2
    ));
    result.setScale(sf::Vector2f(1., PORTAL_HEIGHT_RATIO));
    auto color = portal->used ? sf::Color(100, 0, 255) : sf::Color(255, 0, 0);
    if (portal->lifetime > 0) {
        auto glow_phase = 0.5 * (PORTAL_ACTIVE_SECONDS - portal->lifetime) * 2. * 3.14159;
        color.g = 160. * std::max(sin(glow_phase) * sin(glow_phase), 0.);
    }
    result.setFillColor(color);
    return result;
};

bool GameView::draw(double time) {
    floorView.DrawBackground();

    for(int layer = Z_PLANES - 1; layer >= 0; layer--) {

        for(FloorThing* floorThing: model.getFloorThings()) {
            Portal* portal = dynamic_cast<Portal*>(floorThing);
            if (portal == NULL)
                continue;

            if (floorThing->getType() != EntityType::Portal) {
                continue;
            }

            if(portal->coords.z == layer) {
                auto [yUp, yDown] = floorView.getBothBaseLines(portal->coords);
                _renderWindow->draw(drawPortal(portal, yUp, time));
                _renderWindow->draw(drawPortal(portal, yDown, time));
            }
        }

        for(Enemy* enemy : model.getEnemies()) {

            if(enemy->coords.z == layer) {
                int id1, id2 = 0;

                switch (enemy->getType()) {
                    case EntityType::ZombieAndCat:
                        id1 = Model::GraphicsId::zombie;
                        id2 = Model::GraphicsId::cat;
                        break;
                    case EntityType::IcebergAndFairy:
                        id1 = Model::GraphicsId::iceberg;
                        id2 = Model::GraphicsId::fairy;
                        break;
                    default:
                        continue;
                }

                auto update = [=](int index, bool otherWorld) {
                    _animations.at(index).setFrameDelay(100. / enemy->coords.x_speed); // see Issue #1
                    _animations.at(index).update(time);
                    adjustSprite(index, enemy, otherWorld);
                    _renderWindow->draw(_sprites.at(index));
                };

                update(id1, false);
                update(id2, true);
            }
        }

        for(int p = 0; p < model.getNumberOfPlayers(); p++) {
            auto player = model.getPlayer(p);
            if(player->coords.z == layer) {
                int id = playerStateToSprite[player->state];
                _animations.at(id).update(time);
                adjustSprite(id, player, false); // TODO: get right
                _renderWindow->draw(_sprites.at(id));
            }
        }
    }

    return true;
}

#pragma warning( disable : 4834 )

bool GameView::setUp() {
    // reserving space is needed, becaus references on vector elements
    // become invalid if a new element is added
    const size_t RESERVE_SPACE = 20;
    _textures.reserve(RESERVE_SPACE);
    _sprites.reserve(RESERVE_SPACE);
    _animations.reserve(RESERVE_SPACE);

    loadAnimation("assets/bastard_standing.png", BASTARD_STANDING_PIXEL_WIDTH, BASTARD_STANDING_PIXEL_HEIGHT, BASTARD_STANDING_FRAME_COUNT);
    loadAnimation("assets/bastard_walking.png", BASTARD_WALKING_PIXEL_WIDTH, BASTARD_WALKING_PIXEL_HEIGHT, BASTARD_WALKING_FRAME_COUNT);
    loadAnimation("assets/bastard_attack.png", BASTARD_ATTACK_PIXEL_WIDTH, BASTARD_ATTACK_PIXEL_HEIGHT, BASTARD_ATTACK_FRAME_COUNT);
    loadAnimation("assets/Zombie_01.png", ZOMBIE_PIXEL_WIDTH, ZOMBIE_PIXEL_HEIGHT, ZOMBIE_FRAME_COUNT);
    loadAnimation("assets/katze_01_small.png", CAT_PIXEL_WIDTH, CAT_PIXEL_HEIGHT, CAT_FRAME_COUNT);
    loadAnimation("assets/Eisberg_01.png", ICEBERG_PIXEL_WIDTH, ICEBERG_PIXEL_HEIGHT, ICEBERG_FRAME_COUNT);
    loadAnimation("assets/Fee_01.png", FAIRY_PIXEL_WIDTH, FAIRY_PIXEL_HEIGHT, FAIRY_FRAME_COUNT);

    return true;
}

bool GameView::tearDown() {
    return true;
}

bool GameView::loadAnimation(const std::string &filename, const unsigned int spriteWidthPx, const unsigned int spriteHeightPx, const int frameCount) {
    _textures.push_back(sf::Texture());
    if(!_textures.back().loadFromFile(filename)) {
        std::cout << "Failed to load texture: " << filename << std::endl;
        return false;
    }

    auto sprite = sf::Sprite(_textures.back());
    sprite.setOrigin(sf::Vector2f(0.5 * spriteWidthPx, spriteHeightPx));
    _sprites.push_back(sprite);

    _animations.push_back(Animation(&_sprites.back(), .1));
    for(int i=0; i<frameCount; ++i)
        _animations.back().addFrame(spriteWidthPx*i, 0, spriteWidthPx, spriteHeightPx);

    return true;
}
