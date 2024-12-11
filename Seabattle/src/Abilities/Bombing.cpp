#include "Abilities/Bombing.hpp"

#include "Abilities/BombingSpec.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

namespace seabattle
{
Bombing::Bombing(const BombingSpec *bombing_spec)
    : ships_manager(bombing_spec->ships_manager)
{}

void Bombing::apply() {
    srand(time(0));

    std::vector<int> undestroyed_ships_indexes; 
    for (int i = 0; i < ships_manager.shipsNumber(); i++) {
        if (ships_manager[i]->status() != Ship::Status::kDestroyed) {
            undestroyed_ships_indexes.push_back(i);
        }
    }
    
    if (undestroyed_ships_indexes.size() == 0) {
        return;
    }

    int random_undestroyed_ship_index = undestroyed_ships_indexes[rand() % undestroyed_ships_indexes.size()];


    std::vector<int> undestroyed_ship_segment_indexes;
    for (int i = 0; i < ships_manager[random_undestroyed_ship_index]->size(); i++) {
        if ((*ships_manager[random_undestroyed_ship_index])[i]->status() != Ship::Segment::Status::kDestroyed) {
            undestroyed_ship_segment_indexes.push_back(i);
        }
    }
    
    if (undestroyed_ship_segment_indexes.size() == 0) {
        return;
    }

    int random_undestroyed_ship_segment_index = rand() % undestroyed_ship_segment_indexes.size();

    (*ships_manager[random_undestroyed_ship_index])[random_undestroyed_ship_segment_index]->dealDamage(1);

    std::cout << "Bombing applied\n";
}

} // namespace seabattle