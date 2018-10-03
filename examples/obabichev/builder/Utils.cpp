#include "Utils.h"

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"

namespace sc2 {

Point2D Utils::getCoordinates(const ObservationInterface *observation, UnitTypeID unitType) {
    auto units = observation->GetUnits(Unit::Alliance::Self, IsUnit(unitType));
    if (units.size() == 0) {
        return Point2D(0, 0);
    }
    auto pos = units.front()->pos;
    return {pos.x, pos.y};
}

}