#include <FloorThing.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <GameLogic.h>

FloorThing::FloorThing(FloorThingType type, WorldPosition position) :
        Entity(position), type(type) {
    // could switch type here, i.e. Portals should be a primitive, but Medikit have a sprite.
}

auto drawPortal = [](FloorThing* floory, sf::RenderWindow* window, double time) {
    auto halfwidth = floory->size * PORTAL_MAX_HALFWIDTH;
    auto result = sf::CircleShape(halfwidth);
    result.setPosition(sf::Vector2f(floory->x - halfwidth, floory->y - halfwidth * PORTAL_HEIGHT_RATIO + 2));
    result.setScale(sf::Vector2f(1., PORTAL_HEIGHT_RATIO));
    auto color = sf::Color(255, 0, 0);
    if (floory->lifetime > 0) {
        auto glow_phase = 0.5 * (PORTAL_ACTIVE_SECONDS - floory->lifetime) * 2. * 3.14159;
        color.g = 160. * std::max(sin(glow_phase) * sin(glow_phase), 0.);
    }
    result.setFillColor(color);
    window->draw(result);
};

void FloorThing::customDraw(sf::RenderWindow *window, double time) {
    switch (type) {
        case FloorThingType::Portal:
            drawPortal(this, window, time);
            break;
        // ... did I say: no other type yet?
    }
}
