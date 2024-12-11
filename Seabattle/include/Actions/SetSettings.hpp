#ifndef SET_SETTINGS_HPP
#define SET_SETTINGS_HPP

#include "Action.hpp"

#include <iostream>

namespace seabattle
{

class SetSettings : public Action {

public:

    SetSettings(int game_map_width, int game_map_height, std::vector<int>& ship_sizes);

    ~SetSettings();

    void execute(Game& game) override;

private:
    int game_map_width;
    int game_map_height;
    std::vector<int> ship_sizes;
};

} // namespace seabattle


#endif // SET_SETTINGS_HPP