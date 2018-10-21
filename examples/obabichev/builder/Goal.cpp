//
// Created by Babichev Oleg on 25/09/2018.
//

#include <iostream>
#include "Goal.h"

bool sc2::Goal::isCompleted() {
    return _isCompleted;
}

bool sc2::Goal::hasFailed() {
    return _isFailed;
}

int sc2::Goal::terminate() {
    return 0;
}

void sc2::Goal::setCompleted() {
    std::cout << "Goal::setCompleted.isCompleted " << std::endl;
    _isCompleted = true;
}


sc2::Goal::Goal() {
    std::cout << "CONSTRUCTO Goal" << std::endl;
}

void sc2::Goal::setFailed() {
    _isFailed = true;
}

void sc2::Goal::activate() {
    if (!_isActivated) {
        _isActivated = true;
        onActivate();
    }
}

void sc2::Goal::onActivate() {

}

bool sc2::Goal::isActivated() {
    return _isActivated;
}
