#pragma once

#include <iostream>

#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_agent.h"
#include "sc2api/sc2_map_info.h"

#include "builder/Builder.h"

namespace sc2 {

class Bbot : public Agent {
private:
    Builder builder;

public:
    Bbot();

    void OnGameStart() final;

    void OnStep() final;

    void OnUnitIdle(const Unit *unit) override;

    void OnUnitCreated(const Unit *unit) override;

    const ObservationInterface *observation();
};

}

