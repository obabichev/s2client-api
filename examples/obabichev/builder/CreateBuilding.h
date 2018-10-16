//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_CREATEBUILDING_H
#define S2CLIENT_API_CREATEBUILDING_H

#include <sc2api/sc2_typeenums.h>
#include <sc2api/sc2_unit.h>
#include <../Observable.h>
#include "Goal.h"
#include "Builder.h"

namespace sc2 {

class CreateBuilding : public Goal, public Observable {
private:
    Builder *builder;

    ABILITY_ID buildingType;

    const Unit *worker = nullptr;

    const Unit *building = nullptr;

    bool isBuildingStarted = false;

    bool isWorkerMovedToBuild = false;
public:
    CreateBuilding(Builder *builder1, ABILITY_ID buildingType);

    CreateBuilding(const CreateBuilding &createBuilding);

    GoalStatus process() override;

    void notify(Telegram &telegram) override;
};

}

#endif //S2CLIENT_API_CREATEBUILDING_H
