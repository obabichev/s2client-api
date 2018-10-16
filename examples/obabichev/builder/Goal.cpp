//
// Created by Babichev Oleg on 25/09/2018.
//

#include <iostream>
#include "Goal.h"

bool sc2::Goal::isCompleted() {
    return _isCompleted;
}

bool sc2::Goal::hasFailed() {
    return false;
}

int sc2::Goal::terminate() {
    return 0;
}

void sc2::Goal::setCompleted(bool isCompleted) {
    std::cout << "Goal::setCompleted.isCompleted " << isCompleted << std::endl;
    _isCompleted = isCompleted;
}


sc2::Goal::Goal() {
    std::cout << "CONSTRUCTO Goal" << std::endl;
}
