#ifndef SHIP_HPP_
#define SHIP_HPP_

#include <cstdint>
#include <vector>

namespace battleship
{

class Ship {
public:

    enum class Status : int {
        kIntact,
        kDamaged,
        kDestroyed
    };
    
    enum class Orientation : int {
        kHorizontal,
        kVertical,
    };

    Ship();
    
    explicit Ship(uint32_t size);

    Ship(const Ship& other);

    Ship(Ship&& other);

    ~Ship();

    Ship& operator=(const Ship& other);
    
    Ship& operator=(Ship&& other);
    
    int maxSegmentHealth() const;
    
    uint32_t size() const;

    Ship::Status status() const;
    
    int segmentHealth(uint32_t segment_index) const;

    void damageSegment(uint32_t segment_index, int damage);

    void repairSegment(uint32_t segment_index, int recoveryHealth);

private:
    class Segment {
    public:
        
        Segment();

        Segment(uint32_t max_health);

        ~Segment();

        int health() const;

        Status status() const;

        void dealDamage(int damage);
        
        void increaseHealth(int recoveryHealth);

    private:
        int max_health_;
        int health_;
    
    };

    const int kMaxSegmentHealth;
    std::vector<Ship::Segment> ship_segments_;
};

} // battleship


#endif // SHIP_HPP_