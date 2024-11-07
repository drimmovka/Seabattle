#include "GameMapViewModel.hpp"

#include "GameMap.hpp"

#include <vector>

namespace battleship
{

GameMapViewModel::Cell::Cell()
    : content(Content::kSea)
    , ship_segment_health(-1)
    , shotted(false)
{}

void GameMapViewModel::Cell::reset() {
    content = Content::kSea;
    ship_segment_health = -1;
    shotted = false;
}

GameMapViewModel::GameMapViewModel(GameMap& game_map)
    : game_map_(game_map)
    , width_(game_map.width())
    , height_(game_map.height())
    , cells_(std::vector<std::vector<Cell>> (height_, std::vector<Cell> (width_, Cell())))
{}

int GameMapViewModel::width() const {
    return width_;
}

int GameMapViewModel::height() const {
    return height_;
}

void GameMapViewModel::update() {
    this->clear();

    for (auto& [ship, ship_location] : game_map_.shipToShipLocation()) {
        for (auto& [coords, segment] : ship_location->coords_to_segment) {
            this->setContentValue(coords, Cell::Content::kShipSegment);
            this->setShipSegmentHealthValue(coords, segment->health());
        }
    }

    for (auto& shot_coords : game_map_.shotsCoords()) {
        this->setShottedValue(shot_coords, true);
    }
}

const GameMapViewModel::Cell& GameMapViewModel::at(Coords coords) const {
    if (!this->coordsAreValid(coords)) {
        // throw error
    }
    return cells_[coords.y][coords.x];
}

void GameMapViewModel::clear() {
    for (auto& cells_row : cells_) {
        for (auto& cell : cells_row) {
            cell.reset();
        }
    }
}

bool GameMapViewModel::coordsAreValid(Coords coords) const {
    return (coords.x >= 0 && coords.x <= width_ &&
            coords.y >= 0 && coords.y <= height_);
}

void GameMapViewModel::setContentValue(Coords coords, Cell::Content content_value) {
    if (!this->coordsAreValid(coords)) {
        return; // throw error
    }
    cells_[coords.y][coords.x].content = content_value;
}

void GameMapViewModel::setShipSegmentHealthValue(Coords coords, int ship_segment_health_value) {
    if (!this->coordsAreValid(coords)) {
        return; // throw error
    }
    cells_[coords.y][coords.x].ship_segment_health = ship_segment_health_value;
}

void GameMapViewModel::setShottedValue(Coords coords, bool shotted_value) {
    if (!this->coordsAreValid(coords)) {
        return; // throw error
    }
    cells_[coords.y][coords.x].shotted = shotted_value;
}

} // battleship