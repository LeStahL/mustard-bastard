#pragma once

class Player;

class PlayerAttachable
{
    Player *_player;
    
    public:
    PlayerAttachable() = default;

    Player *player();
    bool isAttachedToPlayer();
};
