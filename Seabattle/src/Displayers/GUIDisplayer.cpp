#include "Displayers/GUIDisplayer.hpp"

#include "GameMapViewModel.hpp"


namespace seabattle
{

GUIDisplayer::GUIDisplayer()
    : window_(sf::VideoMode(1280, 720), "CONSTANT NAME")
    , cell_size_(40)
    , line_width_(4)
{}

void GUIDisplayer::render(GameMapViewModel& game_map_view_model) {
    while (window_.isOpen()) {
        sf::Event event;
        while (window_.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_.close();
            }
        }
        window_.clear();
        
        this->renderGameMap(game_map_view_model, 0);
        this->renderGameMap(game_map_view_model, 1);
        
        window_.display();
    }
}

void GUIDisplayer::renderGameMap(GameMapViewModel& game_map_view_model, int type) {
    game_map_view_model.update();

    if (type == 0) {
        this->renderUnionGameMap(game_map_view_model);
    }

    if (type == 1) {
        this->renderEnemyGameMap(game_map_view_model);
    }
    
}

void GUIDisplayer::renderUnionGameMap(GameMapViewModel& game_map_view_model) {
    Coords top_left = {40, 40};
        
    sf::RectangleShape line; // make vertical line and horizontal line
    line.setFillColor(sf::Color::White);

    // vertical
    line.setSize(sf::Vector2f( line_width_, line_width_ + game_map_view_model.height() * (cell_size_ + line_width_) ));
    for (int x = 0; x <= game_map_view_model.width(); x++) {
        line.setPosition(top_left.x + x * (line.getSize().x + cell_size_), top_left.y);
        window_.draw(line);
    }

    // horizontal
    line.setSize(sf::Vector2f( game_map_view_model.width() * (cell_size_ + line_width_) + line_width_, line_width_ ));
    for (int y = 0; y <= game_map_view_model.height(); y++) {
        line.setPosition(top_left.x, top_left.y + y * (line.getSize().y + cell_size_));
        window_.draw(line);
    }

    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(cell_size_, cell_size_));

    for (int y=0; y<game_map_view_model.height(); y++) {
        for (int x=0; x<game_map_view_model.width(); x++) {
            cell.setPosition(top_left.x + x * (cell_size_ + line_width_) + line_width_, top_left.y + y * (cell_size_ + line_width_) + line_width_);
            if (game_map_view_model.at({x, y}).content == GameMapViewModel::Cell::Content::kSea ) {
                cell.setFillColor(sf::Color::Blue);
            } else {
                cell.setFillColor(sf::Color::Green);
            }
            if (game_map_view_model.at({x, y}).shotted) {
                cell.setOutlineThickness(4);
                cell.setOutlineColor(sf::Color::Red);
            }
            window_.draw(cell);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::White);
        }
    }
}

void GUIDisplayer::renderEnemyGameMap(GameMapViewModel& game_map_view_model) {
    Coords top_left = {700, 40};
        
    sf::RectangleShape line; // make vertical line and horizontal line
    line.setFillColor(sf::Color::White);

    // vertical
    line.setSize(sf::Vector2f( line_width_, line_width_ + game_map_view_model.height() * (cell_size_ + line_width_) ));
    for (int x = 0; x <= game_map_view_model.width(); x++) {
        line.setPosition(top_left.x + x * (line.getSize().x + cell_size_), top_left.y);
        window_.draw(line);
    }

    // horizontal
    line.setSize(sf::Vector2f( game_map_view_model.width() * (cell_size_ + line_width_) + line_width_, line_width_ ));
    for (int y = 0; y <= game_map_view_model.height(); y++) {
        line.setPosition(top_left.x, top_left.y + y * (line.getSize().y + cell_size_));
        window_.draw(line);
    }

    sf::RectangleShape cell;
    cell.setSize(sf::Vector2f(cell_size_, cell_size_));
    
    for (int y=0; y<game_map_view_model.height(); y++) {
        for (int x=0; x<game_map_view_model.width(); x++) {
            cell.setPosition(top_left.x + x * (cell_size_ + line_width_) + line_width_, top_left.y + y * (cell_size_ + line_width_) + line_width_);
            
            if (game_map_view_model.at({x, y}).shotted) {
                cell.setOutlineThickness(4);
                cell.setOutlineColor(sf::Color::Red);
                if (game_map_view_model.at({x, y}).content == GameMapViewModel::Cell::Content::kShipSegment) {
                    cell.setFillColor(sf::Color::Green);
                }
            } else {
                cell.setOutlineThickness(1);
                cell.setOutlineColor(sf::Color::White);
                cell.setFillColor(sf::Color::Blue);

            }
            window_.draw(cell);
        }
    }
}

} // namespace seabattle