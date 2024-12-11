#ifndef SHIP_HPP
#define SHIP_HPP

#include "Coords.hpp"

#include <unordered_map>
#include <vector>

namespace seabattle
{

class Ship {

public:
    class Segment {
    public:
        
        enum class Status : int {
            kIntact,
            kDamaged,
            kDestroyed
        };

        explicit Segment(int max_health = 0);

        ~Segment();

        int health() const;

        Status status() const;

        void dealDamage(int damage);
        
    private:
        const int kMaxHealth;
        int health_;
    };
    
    enum class Status : int {
        kIntact,
        kDamaged,
        kDestroyed
    };
    
    enum class Orientation : int {
        kHorizontal,
        kVertical,
    };

    explicit Ship(int size = 1);

    Ship(const Ship& other);

    Ship(Ship&& other);

    ~Ship();

    Ship& operator=(const Ship& other);
    
    Ship& operator=(Ship&& other);

    Ship::Segment *operator[](int segment_index);
    
    int size() const;

    int maxSegHealth() const;

    int id() const;

    Ship::Status status() const;

    void setId(int id);

    void placeOnGameMap();

    void removeFromGameMap();

    bool placedOnGameMap();

private:
    int id_;
    const int kMaxSegmentHealth;
    bool placed_on_game_map_;
    std::vector<Ship::Segment *> segments_;
};

} // namespace seabattle


#endif // SHIP_HPP