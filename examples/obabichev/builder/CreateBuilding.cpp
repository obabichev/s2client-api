
#include <iostream>
#include <UnitCreatedTelegram.h>
#include <MessageDispatcher.h>
#include "sc2api/sc2_interfaces.h"
#include "CreateBuilding.h"

namespace sc2 {

CreateBuilding::CreateBuilding(Builder *builder, ABILITY_ID buildingType)
    : builder(builder), buildingType(buildingType), Goal() {
    std::cout << "CONSTURCTOR CreateBuilding" << std::endl;
}

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
//    std::cout << "isBuildingStarted" << isBuildingStarted << std::endl;
//    std::cout << "isWorkerMovedToBuild" << isWorkerMovedToBuild << std::endl;

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

    if (building != nullptr) {
//        std::cout << "Build progress: " << building->build_progress << std::endl;
        if (building->build_progress == 1) {
            setCompleted();
            std::cout << "Building completed" << std::endl;
            return GoalStatus::COMPLETED;
        }
        return GoalStatus::ACTIVE;
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

void CreateBuilding::notify(Telegram &telegram) {
    auto &unitCreatedTelegram = dynamic_cast<UnitCreatedTelegram &>(telegram);

    if (unitCreatedTelegram.getUnit()->unit_type == abilityToType(buildingType)) {
        building = unitCreatedTelegram.getUnit();
        isBuildingStarted = true;
        std::cout << "Pylon was started to build!!!!!" << std::endl;
    } else {
        std::cout << "Not right building" << std::endl;
    }
}

CreateBuilding::CreateBuilding(const CreateBuilding &createBuilding) : Goal(createBuilding) {
    std::cout << "COPY CONSTRUCTOR" << std::endl;
}

int CreateBuilding::terminate() {
    std::cout << "Terminate Building creating" << std::endl;
    MessageDispatcher::instance()->detach(TelegramType::UNIT_CREATED);
    return 0;
}

void CreateBuilding::onActivate() {
    std::cout << "Activate building creating" << std::endl;
    MessageDispatcher::instance()->attach(TelegramType::UNIT_CREATED, this);
}

UNIT_TYPEID CreateBuilding::abilityToType(ABILITY_ID ability_id) {
    if (ability_id == ABILITY_ID::BUILD_GATEWAY) {
        return UNIT_TYPEID::PROTOSS_GATEWAY;
    }
    if (ability_id == ABILITY_ID::BUILD_CYBERNETICSCORE) {
        return UNIT_TYPEID::PROTOSS_CYBERNETICSCORE;
    }
    return UNIT_TYPEID::PROTOSS_PYLON;
}

}
