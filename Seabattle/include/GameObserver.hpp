#ifndef GAME_OBSERVER_HPP
#define GAME_OBSERVER_HPP

#include <cstddef>

namespace seabattle
{

class GameObserver {
public:
    GameObserver();

    void bind(bool *should_be_displayed);

    bool shouldBeDisplayed();
    
private:

    bool *_should_be_displayed;

    void resetState();

};

} // namespace seabattle


#endif // GAME_OBSERVER_HPP