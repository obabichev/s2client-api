//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_CREATEBUILDING_H
#define S2CLIENT_API_CREATEBUILDING_H

#include <sc2api/sc2_typeenums.h>
#include "Goal.h"

namespace sc2 {

class CreateBuilding : public Goal {
private:
    UNIT_TYPEID buildingType;
public:
    explicit CreateBuilding(UNIT_TYPEID buildingType);

    GoalStatus process() override;
};

}

#endif //S2CLIENT_API_CREATEBUILDING_H
