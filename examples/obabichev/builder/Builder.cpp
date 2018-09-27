//
// Created by Babichev Oleg on 25/09/2018.
//

#include <iostream>
#include <sc2api/sc2_api.h>
//#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "Builder.h"
#include "Utils.h"

namespace sc2 {

void Builder::update() {
    std::cout << "Builder::update()" << std::endl;
    goal->process();

    tryBuildPylon();

//    auto coordinate = Utils::getCoordinates(observation(), UNIT_TYPEID::PROTOSS_NEXUS);
//    std::cout << "coordinates.x " << coordinate.x << std::endl;
//    std::cout << "coordinates.y " << coordinate.y << std::endl;

//    std::cout << "observation()->GetFoodCap()" << observation()->GetFoodCap() << std::endl;
//    std::cout << "observation()->GetFoodUsed()" << observation()->GetFoodUsed() << std::endl;
}

bool Builder::tryBuildPylon() {

//    const ObservationInterface *observation = Observation();

    // If we are not supply capped, don't build a supply depot.
    if (observation()->GetFoodUsed() < observation()->GetFoodCap() - 6) {
        return false;
    }

    if (observation()->GetMinerals() < 100) {
        return false;
    }

    //check to see if there is already on building
    Units units = observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::PROTOSS_PYLON));
    if (observation()->GetFoodUsed() < 40) {
        for (const auto &unit : units) {
            if (unit->build_progress != 1) {
                return false;
            }
        }
    }

    auto coordinate = Utils::getCoordinates(observation(), UNIT_TYPEID::PROTOSS_NEXUS);

    // Try and build a pylon. Find a random Probe and give it the order.
    float rx = GetRandomScalar();
    float ry = GetRandomScalar();
    Point2D build_location = Point2D(coordinate.x + rx * 15, coordinate.y + ry * 15);
    return tryBuildStructure(ABILITY_ID::BUILD_PYLON, UNIT_TYPEID::PROTOSS_PROBE, build_location);
}

bool Builder::tryBuildStructure(AbilityID ability_type_for_structure, UnitTypeID unit_type, Point2D location,
                                bool isExpansion) {
//    const ObservationInterface* observation = Observation();
    Units workers = observation()->GetUnits(Unit::Alliance::Self, IsUnit(unit_type));

    //if we have no workers Don't build
    if (workers.empty()) {
        return false;
    }

    // Check to see if there is already a worker heading out to build it
    for (const auto &worker : workers) {
        for (const auto &order : worker->orders) {
            if (order.ability_id == ability_type_for_structure) {
                return false;
            }
        }
    }
    // If no worker is already building one, get a random worker to build one
    const Unit *unit = GetRandomEntry(workers);
    // Check to see if unit can make it there
    if (query()->PathingDistance(unit, location) < 0.1f) {
        return false;
    }
//    if (!isExpansion) {
//        for (const auto &expansion : expansions_) {
//            if (Distance2D(location, Point2D(expansion.x, expansion.y)) < 7) {
//                return false;
//            }
//        }
//    }
    // Check to see if unit can build there
    if (query()->Placement(ability_type_for_structure, location)) {
        action()->UnitCommand(unit, ability_type_for_structure, location);
        return true;
    }
    return false;
}

Builder::Builder(Agent *agent) : agent(agent) {}

const ObservationInterface *Builder::observation() {
    return agent->Observation();
}

QueryInterface *Builder::query() {
    return agent->Query();
}

ActionInterface *Builder::action() {
    return agent->Actions();
}

}