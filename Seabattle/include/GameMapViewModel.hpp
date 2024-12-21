#ifndef GAME_MAP_VIEW_MODEL_HPP
#define GAME_MAP_VIEW_MODEL_HPP

#include "GameMap.hpp"

#include <vector>

namespace seabattle
{

class GameMapViewModel {

public:
    struct Cell {
        
        enum class Content : int {
            kShipSegment,
            kSea
        };

        Cell();
        
        void reset();

        Content content;
        int ship_segment_health;
        bool shotted;
    };

    GameMapViewModel(GameMap& game_map);

    int width() const;

    int height() const;

    void update();
    
    const Cell& at(Coords coords) const;

private:
    GameMap& game_map_;
    int width_;
    int height_;
    std::vector<std::vector<Cell>> cells_;
    
    void clear();

    bool coordsAreValid(Coords coords) const;

    void setContentValue(Coords coords, Cell::Content content_value);
    
    void setShipSegmentHealthValue(Coords coords, int ship_segment_health_value);

    void setShottedValue(Coords coords, bool shotted_value);
};

} // namespace seabattle

#endif // GAME_MAP_VIEW_MODEL_HPP