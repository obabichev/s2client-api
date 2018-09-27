#include "Bbot.h"

#include <iostream>

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"

namespace sc2 {

void Bbot::OnGameStart() {
    std::cout << "Start bot" << std::endl;
}

void Bbot::OnStep() {
//    std::cout << Observation()->GetGameLoop() << std::endl;
    builder.update();
}

void Bbot::OnUnitIdle(const Unit *unit) {
    std::cout << "Unit idle: " << unit->unit_type.to_string() << std::endl;
    std::cout << "tag: " << unit->tag << std::endl;
    switch (unit->unit_type.ToType()) {
        case UNIT_TYPEID::PROTOSS_NEXUS: {
            Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_PROBE);
            break;
        }
        default: {
            break;
        }
    }

}

Bbot::Bbot() : builder(Builder(this)) {

}

const ObservationInterface *Bbot::observation() {
    return Observation();
}

}