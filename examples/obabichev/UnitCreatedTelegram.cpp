//
// Created by Babichev Oleg on 06/10/2018.
//

#include "UnitCreatedTelegram.h"

namespace sc2 {

UnitCreatedTelegram::UnitCreatedTelegram(const Unit *unit) : unit(unit) {
}

const Unit *UnitCreatedTelegram::getUnit() {
    return unit;
}

}
