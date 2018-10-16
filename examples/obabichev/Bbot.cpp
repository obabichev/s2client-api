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
    switch (unit->unit_type.ToType()) {
        case UNIT_TYPEID::PROTOSS_NEXUS: {
//            Actions()->UnitCommand(unit, ABILITY_ID::TRAIN_PROBE);
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

void Bbot::OnUnitCreated(const Unit *unit) {
    UnitCreatedTelegram t = UnitCreatedTelegram(unit);
    std::cout << "unit created " << unit->unit_type.to_string() << " " << unit->tag << std::endl;
    MessageDispatcher::instance()->dispatch(TelegramType::UNIT_CREATED, t);
}

}