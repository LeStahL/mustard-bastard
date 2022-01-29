#include <Player.h>
#include <WorldPosition.h>

Player::Player() :
Entity(WorldPosition(0.0, 0, true)) {}

Player::Player(WorldPosition position) :
Entity(position) {}