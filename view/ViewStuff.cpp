#include "ViewStuff.h"

#include <const.h>

ViewStuff::ViewStuff(sf::RenderWindow *window) :
        window(window),
        IsDrawable(0, IsDrawable::DrawType::primitive)
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

auto drawLinesForWorld = [](int sign, sf::Color color, sf::RenderWindow *window)
{
    double center = 0.5 * (HEIGHT + sign * MIDDLE_MARGIN);
    auto line = createHorizontalLine(center, WIDTH, FLOOR_LINE_THICKNESS, color);
    for (int l = 0; l < LINES; l++)
    {
        window->draw(line);
        line.move(sf::Vector2f(0, sign * LINE_DISTANCE));
    }
};

auto drawMargin = [](sf::RenderWindow *window)
{
    window->draw(createHorizontalLine(0.5 * HEIGHT, WIDTH, MIDDLE_MARGIN, MARGIN_COLOR));
};

auto drawBackground = [](int sign, sf::Color color, sf::RenderWindow *window)
{
    double y = sign == -1 ? 0 : 0.5 * HEIGHT;
    auto rect = sf::RectangleShape(sf::Vector2f(WIDTH, 0.5 * HEIGHT));
    rect.setPosition(sf::Vector2f(0, y));
    rect.setFillColor(color * sf::Color(255, 255, 255, 40));
    window->draw(rect);
};

void ViewStuff::DrawBackground()
{
    drawBackground(-1, TOP_COLOR, window);
    drawLinesForWorld(-1, TOP_COLOR, window);
    drawBackground(+1, BOTTOM_COLOR, window);
    drawLinesForWorld(+1, BOTTOM_COLOR, window);
    drawMargin(window);
}

void ViewStuff::customDraw(double time) {
    DrawBackground();
}