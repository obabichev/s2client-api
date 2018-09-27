//
// Created by Babichev Oleg on 25/09/2018.
//

#include "Goal.h"

bool sc2::Goal::isCompleted() {
    return false;
}

bool sc2::Goal::hasFailed() {
    return false;
}

int sc2::Goal::terminate() {
    return 0;
}

sc2::Goal::Goal() = default;
