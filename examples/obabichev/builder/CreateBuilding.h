//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_CREATEBUILDING_H
#define S2CLIENT_API_CREATEBUILDING_H

#include <sc2api/sc2_typeenums.h>
#include <sc2api/sc2_unit.h>
#include "Goal.h"
#include "Builder.h"

namespace sc2 {

class CreateBuilding : public Goal {
private:
    Builder *builder;

    ABILITY_ID buildingType;

    const Unit *worker = nullptr;

    bool isBuildingStarted = false;

    bool isWorkerMovedToBuild = false;
public:
    CreateBuilding(Builder *builder1, ABILITY_ID buildingType);

    GoalStatus process() override;
};

}

#endif //S2CLIENT_API_CREATEBUILDING_H
