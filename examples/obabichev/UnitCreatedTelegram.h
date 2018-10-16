//
// Created by Babichev Oleg on 06/10/2018.
//

#ifndef S2CLIENT_API_UNITCREATEDTELEGRAM_H
#define S2CLIENT_API_UNITCREATEDTELEGRAM_H

#include "Telegram.h"
#include "sc2api/sc2_unit.h"

namespace sc2 {

class UnitCreatedTelegram : public Telegram {
private:
    const Unit *unit;

public:
    explicit UnitCreatedTelegram(const Unit *unit);

    const Unit *getUnit();
};

}

#endif //S2CLIENT_API_UNITCREATEDTELEGRAM_H
