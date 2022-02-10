#pragma once

#include <map>
#include <IsDrawable.hpp>
#include <SFML/System.hpp>

enum FloorThingType {
    Portal,
    // Medikit,
    // etc.
};

class FloorThing : public IsDrawable {
    // hack: just make everything public so we can pfriemel around in it
    public:
    FloorThingType type;
    float size = 1;
    bool spawning = true;
    float lifetime = 0;

    FloorThing(FloorThingType type, WorldPosition position);
    void endLife();

    void customDraw(sf::RenderWindow *window, double time) override;
};
