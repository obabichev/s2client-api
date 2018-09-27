//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_BUILDER_H
#define S2CLIENT_API_BUILDER_H

#include "Goal.h"
#include "FollowBuildOrderGoal.h"

namespace sc2 {

class Builder {
private:
    Goal *goal = new FollowBuildOrderGoal();

    Agent *agent;

    bool tryBuildPylon();

    bool tryBuildStructure(AbilityID ability_type_for_structure, UnitTypeID unit_type, Point2D location,
                           bool isExpansion = false);

public:
    explicit Builder(Agent *agent);

    void update();

    const ObservationInterface *observation();

    QueryInterface *query();

    ActionInterface *action();
};

}

#endif //S2CLIENT_API_BUILDER_H
