//
// Created by Babichev Oleg on 25/09/2018.
//

#include <iostream>
#include "CreateBuilding.h"

namespace sc2 {

GoalStatus CreateBuilding::process() {
    std::cout << "CreateBuilding::process buildingType=" << static_cast<int>(buildingType) << std::endl;



    return GoalStatus::ACTIVE;
}

CreateBuilding::CreateBuilding(UNIT_TYPEID buildingType) : buildingType(buildingType) {}

}
