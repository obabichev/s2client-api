//
// Created by Babichev Oleg on 25/09/2018.
//

#include "FollowBuildOrderGoal.h"
#include "CreateBuilding.h"

namespace sc2 {

FollowBuildOrderGoal::FollowBuildOrderGoal(Builder *builder) : builder(builder) {
    subgoals.push_back(new CreateBuilding(builder, ABILITY_ID::BUILD_PYLON));
    subgoals.push_back(new CreateBuilding(builder, ABILITY_ID::BUILD_GATEWAY));
    subgoals.push_back(new CreateBuilding(builder, ABILITY_ID::BUILD_CYBERNETICSCORE));
}

}
