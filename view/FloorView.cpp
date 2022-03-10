#include <FloorView.hpp>

#include <const.hpp>
#include <utility>

FloorView::FloorView(sf::RenderWindow *window) :
        window(window)
{ }

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
    double center = 0.5 * (GAME_HEIGHT + sign * MIDDLE_MARGIN);
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

auto drawMiddleMargin = [](sf::RenderWindow *window)
{
    window->draw(
        createHorizontalLine(0.5 * (GAME_HEIGHT + MIDDLE_MARGIN), WIDTH, MIDDLE_MARGIN, MARGIN_COLOR)
    );
};

auto drawBackground = [](bool upWorld, sf::Color color, sf::RenderWindow *window)
{
    double y = upWorld ? 0 : 0.5 * GAME_HEIGHT;
    auto rect = sf::RectangleShape(sf::Vector2f(WIDTH, 0.5 * GAME_HEIGHT));
    rect.setPosition(sf::Vector2f(0, y));
    rect.setFillColor(color * sf::Color(255, 255, 255, 40));
    window->draw(rect);
};

void FloorView::DrawBackground()
{
    drawBackground(true, TOP_COLOR, window);
    drawLinesForWorld(true, TOP_COLOR, window);
    drawBackground(false, BOTTOM_COLOR, window);
    drawLinesForWorld(false, BOTTOM_COLOR, window);
    drawMiddleMargin(window);
}

void FloorView::customDraw(sf::RenderWindow *window, double time) {
    DrawBackground();
}

auto baseLineFor = [](int z, bool upWorld) {
    return (int)(0.5 * (yForLine(z, upWorld) + yForLine(z + 1, upWorld)));
};

int FloorView::getBackgroundBaseLine(WorldCoordinates coords) {
    return baseLineFor(coords.z, coords.upWorld);
}

std::pair<int, int> FloorView::getBothBaseLines(WorldCoordinates coords) {
    return std::pair(baseLineFor(coords.z, true), baseLineFor(coords.z, false));
}
