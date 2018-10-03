
#include <iostream>
#include "sc2api/sc2_interfaces.h"
#include "CreateBuilding.h"

namespace sc2 {

bool isWorkerMoveToBuild(const Unit *worker, ABILITY_ID buildingType) {
    for (const auto &order : worker->orders) {
        if (order.ability_id == buildingType) {
            return true;
        }
    }
    return false;
}

GoalStatus CreateBuilding::process() {
//    std::cout << "CreateBuilding::process buildingType=" << static_cast<int>(buildingType) << std::endl;
    if (!isBuildingStarted && builder->observation()->GetMinerals() < 100) {
        return GoalStatus::ACTIVE;
    }

    if (worker == nullptr) {
        auto newWorker = builder->getWorkerToBuild();
        if (newWorker != nullptr) {
            std::cout << "CreateBuilding::process worker has been chosen " << newWorker->tag << std::endl;
            worker = newWorker;
        } else {
            return GoalStatus::ACTIVE;
        }
    }

    if (!isWorkerMovedToBuild && !isWorkerMoveToBuild(worker, buildingType)) {
//        std::cout << "isBuildingStarted " << isBuildingStarted << std::endl;
//        std::cout << "isWorkerMoveToBuild(worker, buildingType) " << isWorkerMoveToBuild(worker, buildingType)
//                  << std::endl;
        if (builder->tryBuildStructure(worker, buildingType)) {
            isWorkerMovedToBuild = true;
            std::cout << "Worker moved to build structure" << std::endl;
        }
        return GoalStatus::ACTIVE;
    }

    return GoalStatus::ACTIVE;
}

CreateBuilding::CreateBuilding(Builder *builder, ABILITY_ID buildingType)
    : builder(builder), buildingType(buildingType) {}

}
