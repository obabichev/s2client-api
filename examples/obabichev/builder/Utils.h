//
// Created by Babichev Oleg on 27/09/2018.
//

#ifndef S2CLIENT_API_UTILS_H
#define S2CLIENT_API_UTILS_H

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_typeenums.h"
#include "sc2api/sc2_types.h"

namespace sc2 {

class Utils {
public:
    static Point2D getCoordinates(const ObservationInterface *observation, UnitTypeID unitType);
};

}

#endif //S2CLIENT_API_UTILS_H
