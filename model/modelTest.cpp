#include <iostream>

#include <Entity.h>
#include <Player.h>
#include <WorldCoordinates.h>
#include <vector>

using namespace std;

bool test_id_counter();

int main() {

    cout << "Moin, test!" << endl;

    test_id_counter();


    return 0;
}

bool test_id_counter() {
    vector<Entity> entities;

    entities.push_back(Player(0, WorldCoordinates(0.5, 0, true)));
    entities.push_back(Player(0, WorldCoordinates(0.5, 0, true)));

    for(auto it = std::begin(entities); it != std::end(entities); ++it) {
        cout << it->id << endl;
    }

    return true;
}