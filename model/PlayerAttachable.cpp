#include "PlayerAttachable.hpp"
#include "Player.h"

bool PlayerAttachable::isAttachedToPlayer()
{
    return _player != nullptr;
}

Player *PlayerAttachable::player()
{
    return _player;
}
