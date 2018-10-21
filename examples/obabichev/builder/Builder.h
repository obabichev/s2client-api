//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_BUILDER_H
#define S2CLIENT_API_BUILDER_H

#include "Goal.h"
//#include "FollowBuildOrderGoal.h"
#include "sc2api/sc2_agent.h"
#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_common.h"

namespace sc2 {

class Builder {
private:
    Goal *goal;

    Agent *agent;

    Point2D generateLocationForBuilding(AbilityID structureAbilityType);

    Point2D generateLocationNearPylon();

    Tag generateLocationForAssimilator();

public:
    explicit Builder(Agent *agent);

    void update();

    const ObservationInterface *observation();

    QueryInterface *query();

    ActionInterface *action();

    const Unit *getWorkerToBuild();

    bool tryBuildStructure(const Unit *worker, AbilityID structureAbilityType);

    bool tryBuildStructure(const Unit *worker, AbilityID structureAbilityType, Tag tag);

    bool tryBuildAssimilator(const Unit *worker);

    Point2D getRandomLocation();
};

}

#endif //S2CLIENT_API_BUILDER_H
