#include <SFML/Graphics/Color.hpp>

constexpr unsigned int WIDTH = 66 * 16;
constexpr unsigned int HEIGHT = 66 * 9;

constexpr unsigned int MAX_PLAYERS = 2;

constexpr unsigned int Z_PLANES = 3;

constexpr float FLOOR_LINE_THICKNESS = 1.5;
constexpr float LINE_DISTANCE = 32.;
constexpr int LINES = Z_PLANES + 1;
constexpr float MIDDLE_MARGIN = 3;
constexpr float HUD_MARGIN = 0.16 * HEIGHT;
constexpr float GAME_HEIGHT = HEIGHT - HUD_MARGIN;

constexpr sf::Color TOP_COLOR(170, 170, 0);
constexpr sf::Color BOTTOM_COLOR(0, 150, 200);
constexpr sf::Color MARGIN_COLOR(210, 13, 13);
constexpr sf::Color HUD_COLOR(0, 0, 0);
