#pragma once

class NeedsEnemyNotifications {
public:
    virtual ~NeedsEnemyNotifications() {}

    virtual void enemyAdded() = 0;
    virtual void enemyRemoved(int index) = 0;
};
