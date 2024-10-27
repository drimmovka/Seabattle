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

    class Segment {
    public:
        
        explicit Segment(int max_health = 0);

        ~Segment();

        int health() const;

        Status status() const;

        void dealDamage(int damage);
        
    private:
        int max_health_;
        int health_;
    
    };

private:

    const int kMaxSegmentHealth;
    std::vector<Ship::Segment> ship_segments_;

    bool segmentIndexOutOfRange(int segment_index) const;

public:

    explicit Ship(int size = 1);

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

};

} // battleship


#endif // SHIP_HPP_