#include "ViewStuff.h"

#include <const.h>

ViewStuff::ViewStuff(sf::RenderWindow *window) :
        window(window),
        IsDrawable(0, IsDrawable::DrawType::primitive, WorldPosition(0, 0, true))
{ }

constexpr float FLOOR_LINE_THICKNESS = 1.5;
constexpr float LINE_DISTANCE = 32.;
constexpr int LINES = 4;
constexpr float MIDDLE_MARGIN = 3;

constexpr sf::Color TOP_COLOR(170, 170, 0);
constexpr sf::Color BOTTOM_COLOR(0, 150, 200);
constexpr sf::Color MARGIN_COLOR(210, 13, 13);

auto createHorizontalLine = [](float y, float width, float thickness, sf::Color color)
{
    sf::RectangleShape line(sf::Vector2f(width, thickness));
    line.setPosition(sf::Vector2f(0, y - 0.5 * thickness));
    line.setFillColor(color);
    return line;
};

auto yForLine = [](int z, bool upWorld)
{
    int sign = upWorld ? -1 : 1;
    double center = 0.5 * (HEIGHT + sign * MIDDLE_MARGIN);
    return center + sign * z * LINE_DISTANCE;
};

auto drawLinesForWorld = [](bool upWorld, sf::Color color, sf::RenderWindow *window)
{
    auto line = createHorizontalLine(0, WIDTH, FLOOR_LINE_THICKNESS, color);
    for (int l = 0; l < LINES; l++)
    {
        line.setPosition(sf::Vector2f(0, yForLine(l, upWorld)));
        window->draw(line);
    }
};

auto drawMargin = [](sf::RenderWindow *window)
{
    window->draw(createHorizontalLine(0.5 * HEIGHT, WIDTH, MIDDLE_MARGIN, MARGIN_COLOR));
};

auto drawBackground = [](bool upWorld, sf::Color color, sf::RenderWindow *window)
{
    double y = upWorld ? 0 : 0.5 * HEIGHT;
    auto rect = sf::RectangleShape(sf::Vector2f(WIDTH, 0.5 * HEIGHT));
    rect.setPosition(sf::Vector2f(0, y));
    rect.setFillColor(color * sf::Color(255, 255, 255, 40));
    window->draw(rect);
};

void ViewStuff::DrawBackground()
{
    drawBackground(true, TOP_COLOR, window);
    drawLinesForWorld(true, TOP_COLOR, window);
    drawBackground(false, BOTTOM_COLOR, window);
    drawLinesForWorld(false, BOTTOM_COLOR, window);
    drawMargin(window);
}

void ViewStuff::customDraw(double time) {
    DrawBackground();
}

int ViewStuff::getBackgroundBaseLine(WorldPosition position) {
    int z = position.z;
    bool upWorld = position.upWorld;
    return 0.5 * (yForLine(z, upWorld) + yForLine(z + 1, upWorld));
}