#include <GameView.hpp>
#include <iostream>
#include "ViewConst.h"
#include <Entity.h>

std::map<int, int> playerStateToSprite = {
    { PlayerState::Standing , Model::GraphicsId::player_standing },
    { PlayerState::Walking  , Model::GraphicsId::player_walking },
    { PlayerState::Attacking, Model::GraphicsId::player_attack }
};

GameView::GameView(sf::RenderWindow *renderWindow, Model& model) :
    _renderWindow(renderWindow),
    model(model),
    viewStuff(ViewStuff(_renderWindow)) {
}

sf::Vector2f GameView::convertWorldPosition(WorldPosition position) {
    sf::Vector2f pixelPos;

    pixelPos.x = position.x;
    pixelPos.y = viewStuff.getBackgroundBaseLine(position);

    return pixelPos;
}

void GameView::adjustSprite(int spriteId, Entity &entity, bool upworld)
{
    // small hack, not pretty
    WorldPosition pos = entity.position;
    pos.upWorld = upworld;

    sf::Vector2f position = convertWorldPosition(pos);
    sf::Vector2f shift = _spriteCenters.at(spriteId);

    // TODO : replace by pretty math
    if(upworld) {
        float x_sign = entity.orientation.facing_left ? -1 : 1;
        _sprites.at(spriteId).setPosition(position - sf::Vector2f(x_sign * shift.x, shift.y));
        _sprites.at(spriteId).setScale(sf::Vector2f(x_sign, 1));
    } else {
        _sprites.at(spriteId).setRotation(180.0f*(int(upworld)-1));
        float x_sign = entity.orientation.facing_left ? 1 : -1;
        _sprites.at(spriteId).setPosition(position + sf::Vector2f(x_sign * shift.x, shift.y));
        _sprites.at(spriteId).setScale(sf::Vector2f(x_sign, 1));
    }
}

bool GameView::draw(double time) {
    viewStuff.DrawBackground();

    // hack: this is for the Entity <-> IsDrawable sync for Player coordinates etc.
    model.syncDrawableEntities(); // might be redundant now.

/* merge relic
                case IsDrawable::DrawType::primitive:
                    (*it)->customDraw(_renderWindow, time);
                    break;

*/
    
    for(int layer = 2; layer >= 0; layer--) {
        for(Enemy enemy : model.getEnemies()) {
            if(enemy.position.z == layer) {
                int id1, id2 = 0;

                switch (enemy.type) {
                case EnemyType::ZombieAndCat:
                    id1 = Model::GraphicsId::zombie;
                    id2 = Model::GraphicsId::cat;
                    break;
                case EnemyType::IcebergAndFairy:
                    id1 = Model::GraphicsId::iceberg;
                    id2 = Model::GraphicsId::fairy;
                    break;
                }

               _animations.at(id1).update(time);
                adjustSprite(id1, enemy, true);
                _renderWindow->draw(_sprites.at(id1));

                _animations.at(id2).update(time);
                adjustSprite(id2, enemy, false);
                _renderWindow->draw(_sprites.at(id2));
            }
        }

        for(int p = 0; p < model.getNumberOfPlayers(); p++) {
            if(model.getPlayer(p)->position.z == layer) {
                int id = playerStateToSprite[model.getPlayer(p)->state];
                _animations.at(id).update(time);
                adjustSprite(id, *model.getPlayer(p), true); // TODO: get right
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
    _spriteCenters.reserve(RESERVE_SPACE);

    loadAnimation("assets/bastard_standing.png", BASTARD_STANDING_PIXEL_WIDTH, BASTARD_STANDING_PIXEL_HEIGHT, BASTARD_STANDING_FRAME_COUNT);
    loadAnimation("assets/bastard_walking.png", BASTARD_WALKING_PIXEL_WIDTH, BASTARD_WALKING_PIXEL_HEIGHT, BASTARD_WALKING_FRAME_COUNT);
    loadAnimation("assets/bastard_attack.png", BASTARD_ATTACK_PIXEL_WIDTH, BASTARD_ATTACK_PIXEL_HEIGHT, BASTARD_ATTACK_FRAME_COUNT);
    loadAnimation("assets/Zombie_01.png", ZOMBIE_PIXEL_WIDTH, ZOMBIE_PIXEL_HEIGHT, ZOMBIE_FRAME_COUNT);
    loadAnimation("assets/katze_01.png", CAT_PIXEL_WIDTH, CAT_PIXEL_HEIGHT, CAT_FRAME_COUNT);
    loadAnimation("assets/Eisberg_01.png", ICEBERG_PIXEL_WIDTH, ICEBERG_PIXEL_HEIGHT, ICEBERG_FRAME_COUNT);
    loadAnimation("assets/Fee_01.png", FAIRY_PIXEL_WIDTH, FAIRY_PIXEL_WIDTH, FAIRY_FRAME_COUNT);
    
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

    _sprites.push_back(sf::Sprite(_textures.back()));

    _animations.push_back(Animation(&_sprites.back(), .1));
    for(int i=0; i<frameCount; ++i)
        _animations.back().addFrame(spriteWidthPx*i, 0, spriteWidthPx, spriteHeightPx);

    _spriteCenters.push_back(sf::Vector2f(0.5 * spriteWidthPx, spriteHeightPx));

    return true;
}