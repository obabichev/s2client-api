//
// Created by Babichev Oleg on 25/09/2018.
//

#include <iostream>
#include "FollowBuildOrderGoal.h"
#include "CreateBuilding.h"

namespace sc2 {

FollowBuildOrderGoal::FollowBuildOrderGoal() {
    subgoals.push_back(new CreateBuilding(UNIT_TYPEID::PROTOSS_PYLON));
}

}
