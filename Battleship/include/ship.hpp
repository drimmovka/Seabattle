#ifndef SHIP_HPP_
#define SHIP_HPP_

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
    
    explicit Ship(int size);

    Ship(const Ship& other);

    Ship(Ship&& other);

    ~Ship();

    Ship& operator=(const Ship& other);
    
    Ship& operator=(Ship&& other);
    
    int maxSegmentHealth() const;
    
    int size() const;

    Ship::Status status() const;
    
    int segmentHealth(int segment_index) const;

    void damageSegment(int segment_index, int damage);

    void repairSegment(int segment_index, int recoveryHealth);

private:
    class Segment {
    public:
        
        Segment();

        Segment(int max_health);

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