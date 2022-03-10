#include <GameView.hpp>

#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>

#include <ViewConst.hpp>
#include <GameLogic.hpp>
#include <GameLogicConst.hpp>
#include <Entity.hpp>
#include <Portal.hpp>
#include <const.hpp>

std::map<PlayerState, Model::GraphicsId> playerStateToSprite = {
    { PlayerState::Standing, Model::GraphicsId::player_standing },
    { PlayerState::Walking, Model::GraphicsId::player_walking },
    { PlayerState::Attacking, Model::GraphicsId::player_attack },
    { PlayerState::Warping, Model::GraphicsId::player_standing }
};

std::map<WeaponType, Model::GraphicsId> weaponTypeToSprite = {
    { WeaponType::Axe, Model::GraphicsId::axe }
};

const std::map<AnimationType, AnimationAssetInformation> GameView::assetInformations = {
    {AnimationType::BastardStanding, {"assets/bastard_standing.png", BASTARD_STANDING_PIXEL_WIDTH, BASTARD_STANDING_PIXEL_HEIGHT, BASTARD_STANDING_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::BastardWalking, {"assets/bastard_walking.png", BASTARD_WALKING_PIXEL_WIDTH, BASTARD_WALKING_PIXEL_HEIGHT, BASTARD_WALKING_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::BastardAttacking, {"assets/bastard_attack.png", BASTARD_ATTACK_PIXEL_WIDTH, BASTARD_ATTACK_PIXEL_HEIGHT, BASTARD_ATTACK_FRAME_COUNT, BASTARD_ATTACK_FRAME_DELAY}},
    {AnimationType::ZombieWalking, {"assets/Zombie_01.png", ZOMBIE_PIXEL_WIDTH, ZOMBIE_PIXEL_HEIGHT, ZOMBIE_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::CatWalking, {"assets/katze_01_small.png", CAT_PIXEL_WIDTH, CAT_PIXEL_HEIGHT, CAT_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::IcebergSliding, {"assets/Eisberg_01.png", ICEBERG_PIXEL_WIDTH, ICEBERG_PIXEL_HEIGHT, ICEBERG_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::FairyFlying, {"assets/Fee_01.png", FAIRY_PIXEL_WIDTH, FAIRY_PIXEL_HEIGHT, FAIRY_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::Medikit, {"assets/medikit.png", MEDIKIT_PIXEL_WIDTH, MEDIKIT_PIXEL_HEIGHT, MEDIKIT_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::Parachute, {"assets/parachute.png", PARACHUTE_PIXEL_WIDTH, PARACHUTE_PIXEL_HEIGHT, PARACHUTE_FRAME_COUNT, DEFAULT_FRAME_DELAY}},
    {AnimationType::Axe, {"assets/beil.png", AXE_PIXEL_WIDTH, AXE_PIXEL_HEIGHT, AXE_FRAME_COUNT, DEFAULT_FRAME_DELAY}}
};

GameView::GameView(sf::RenderWindow *renderWindow, Model *model) :
    _renderWindow(renderWindow),
    model(model),
    floorView(FloorView(_renderWindow))
{
}

sf::Vector2f GameView::convertWorldCoordinates(WorldCoordinates position) {
    sf::Vector2f pixelPos;

    pixelPos.x = position.x;
    pixelPos.y = floorView.getBackgroundBaseLine(position) - position.y;

    return pixelPos;
}

void GameView::adjustSprite(int spriteId, Entity* entity, bool invertWorld)
{
    // small hack, not pretty - qm: don't get why this was done. I changed it.
    WorldCoordinates pos = entity->coords;
    pos.upWorld ^= invertWorld;

    auto sprite = _animations.at(spriteId).sprite();
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

bool GameView::draw(double time) {
    if(model->getGameState() == Model::GameState::Paused)
        time = 0.0;

    floorView.DrawBackground();

    for(int layer = Z_PLANES - 1; layer >= 0; layer--) {

        for(FloorThing* floorThing: model->getFloorThings()) {
            if(floorThing->coords.z != layer)
                continue;

            switch (floorThing->getType()) {
                case EntityType::Portal:
                    drawPortal(dynamic_cast<Portal*>(floorThing), time);
                    break;
                case EntityType::Medikit:
                    drawMedikit(dynamic_cast<Medikit*>(floorThing), time);
                    break;
                case EntityType::Weapon:
                    drawWeapon(dynamic_cast<Weapon*>(floorThing), time);
                default:
                continue;
            }
        }

        //for(Enemy* enemy : model->getEnemies()) {
        for(std::vector<Enemy*>::iterator it = model->getEnemies().begin(); it != model->getEnemies().end(); it++) {
            Enemy *enemy = *it;
            int enemyIndex = it - model->getEnemies().begin();

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


                auto update = [=](int index, bool otherWorld, int enemyIndex) {
                    //_animations.at(index).setFrameDelay(100. / enemy->coords.x_speed); // see Issue #1
                    _animations.at(index).update(time, enemyLocalPhase.at(enemyIndex));
                    adjustSprite(index, enemy, otherWorld);
                    _renderWindow->draw(*_animations.at(index).sprite());
                };

                update(id1, false, enemyIndex);
                update(id2, true, enemyIndex);
            }
        }

        for(int p = 0; p < model->getNumberOfPlayers(); p++) {
            auto player = model->getPlayer(p);
            if(player->coords.z == layer) { 
                if(player->state == PlayerState::Attacking && player->weapon->type != WeaponType::Hand) {
                    weaponUp = static_cast<bool>(int(time/0.25) % 2);

                    if(weaponUp) {
                        Model::GraphicsId weaponId = weaponTypeToSprite[player->weapon->type];

                        adjustSprite(weaponId, player, false);
                        int x_sign = player->coords.facing_left ? -1 : 1;
                        int y_sign = player->coords.upWorld ? 1 : -1;
                        sf::Vector2f offset(WEAPON_AXE_HAND_X_OFFSET*x_sign, WEAPON_AXE_HAND_Y_OFFSET*y_sign);
                        _animations.at(weaponId).sprite()->move(offset);

                        _renderWindow->draw(*_animations.at(weaponId).sprite());
                    }
                }

                int id = playerStateToSprite[player->state];
                _animations.at(id).update(time);
                adjustSprite(id, player, false); // TODO: get right
                _renderWindow->draw(*_animations.at(id).sprite());
            }
        }
    }

    return true;
}

bool GameView::setUp() {
    for(std::map<AnimationType,AnimationAssetInformation>::const_iterator it = assetInformations.begin(); it != assetInformations.end(); ++it)
        loadAnimationData(it->first, it->second);
    
    return true;
}

bool GameView::tearDown() {
    for(std::map<AnimationType, AnimationData>::iterator it = _animationData.begin(); it != _animationData.end(); ++it)
    {
        delete it->second.texture;
        delete it->second.sprite;
    }

    _animationData.clear();
    _animations.clear();

    return true;
}

auto drawPortalHelper = [](Portal* portal, double y, double time) {
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

void GameView::drawPortal(Portal *portal, double time) {
    auto [yUp, yDown] = floorView.getBothBaseLines(portal->coords);
    _renderWindow->draw(drawPortalHelper(portal, yUp, time));
    _renderWindow->draw(drawPortalHelper(portal, yDown, time));
}

void GameView::drawMedikit(Medikit *medikit, double time) {
    adjustSprite(Model::GraphicsId::medikit, medikit, false);
    _renderWindow->draw(*_animations.at(Model::GraphicsId::medikit).sprite());

    if(medikit->spawning) {
        adjustSprite(Model::GraphicsId::parachute, medikit, false);
        _animations.at(Model::GraphicsId::parachute).sprite()->move(sf::Vector2f(0.0f, MEDIKIT_PARACHUTE_OFFSET));
        _renderWindow->draw(*_animations.at(Model::GraphicsId::parachute).sprite());
    }
}

void GameView::drawWeapon(Weapon *weapon, double time) {
    adjustSprite(Model::GraphicsId::axe, weapon, false);
    _renderWindow->draw(*_animations.at(Model::GraphicsId::axe).sprite());
}

void GameView::enemyAdded()
{
    float localPhase = float((random() % 100)/100.0f);
    enemyLocalPhase.push_back(localPhase);
}

void GameView::enemyRemoved(int index)
{
    std::vector<float>::iterator it = enemyLocalPhase.begin() + index;
    enemyLocalPhase.erase(it);
}

bool GameView::loadAnimationData(AnimationType type, AnimationAssetInformation information) {
    AnimationData data;

    bool result = true;

    data.texture = new sf::Texture();
    result &= data.texture->loadFromFile(information.assetPath);
    data.sprite = new sf::Sprite(*data.texture);
    data.sprite->setOrigin(sf::Vector2f(.5*information.width, information.height));

    _animationData.insert({type, data});

    Animation animation(_animationData.at(type).sprite, information.frameDelay);
    for(int i=0; i<assetInformations.at(type).frameCount; ++i)
        animation.addFrame(assetInformations.at(type).width*i, 0, assetInformations.at(type).width, assetInformations.at(type).height);
    _animations.push_back(animation);

    return result;
}
