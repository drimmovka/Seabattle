#include "GameObserver.hpp"

namespace seabattle
{

GameObserver::GameObserver()
    : _should_be_displayed(nullptr)
{}

void GameObserver::bind(bool *should_be_displayed) {
    _should_be_displayed = should_be_displayed;
}

bool GameObserver::shouldBeDisplayed() {
    bool tmp = *_should_be_displayed;
    this->resetState();
    return tmp;
}

void GameObserver::resetState() {
    *_should_be_displayed = false;
}

} // namespace seabattle