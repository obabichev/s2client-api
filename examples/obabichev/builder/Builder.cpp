//
// Created by Babichev Oleg on 25/09/2018.
//

#include <iostream>
#include <sc2api/sc2_api.h>

#include "Builder.h"
#include "Utils.h"
#include "FollowBuildOrderGoal.h"

namespace sc2 {

struct IsTownHall {
    bool operator()(const Unit &unit) {
        switch (unit.unit_type.ToType()) {
            case UNIT_TYPEID::ZERG_HATCHERY:
                return true;
            case UNIT_TYPEID::ZERG_LAIR:
                return true;
            case UNIT_TYPEID::ZERG_HIVE :
                return true;
            case UNIT_TYPEID::TERRAN_COMMANDCENTER:
                return true;
            case UNIT_TYPEID::TERRAN_ORBITALCOMMAND:
                return true;
            case UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING:
                return true;
            case UNIT_TYPEID::TERRAN_PLANETARYFORTRESS:
                return true;
            case UNIT_TYPEID::PROTOSS_NEXUS:
                return true;
            default:
                return false;
        }
    }
};

struct IsVespeneGeyser {
    bool operator()(const Unit &unit) {
        switch (unit.unit_type.ToType()) {
            case UNIT_TYPEID::NEUTRAL_VESPENEGEYSER:
                return true;
            case UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER:
                return true;
            case UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER:
                return true;
            default:
                return false;
        }
    }
};

void Builder::update() {
    goal->process();

}

Builder::Builder(Agent *agent) : agent(agent) {
    std::cout << "CONSTRUCTOR Builder" << std::endl;
    goal = new FollowBuildOrderGoal(this);
}

const ObservationInterface *Builder::observation() {
    return agent->Observation();
}

QueryInterface *Builder::query() {
    return agent->Query();
}

ActionInterface *Builder::action() {
    return agent->Actions();
}

const Unit *Builder::getWorkerToBuild() {
    Units workers = observation()->GetUnits(Unit::Alliance::Self, IsUnit(UNIT_TYPEID::PROTOSS_PROBE));

    //if we have no workers Don't build
    if (workers.empty()) {
        return nullptr;
    }

    const Unit *unit = GetRandomEntry(workers);

    return unit;
}

bool Builder::tryBuildStructure(const Unit *worker, AbilityID structureAbilityType) {
//    auto location = getRandomLocation();
    auto location = generateLocationForBuilding(structureAbilityType);

    if (query()->Placement(structureAbilityType, location)) {
        action()->UnitCommand(worker, structureAbilityType, location);
        return true;
    }
    return false;
}

bool Builder::tryBuildStructure(const Unit *worker, AbilityID structureAbilityType, Tag tag) {
    const Unit *target = observation()->GetUnit(tag);

    if (query()->Placement(structureAbilityType, target->pos)) {
        action()->UnitCommand(worker, structureAbilityType, target);
        return true;
    }
    return false;
}


Point2D Builder::generateLocationForBuilding(AbilityID structureAbilityType) {
    if (structureAbilityType == ABILITY_ID::BUILD_PYLON) {
        return getRandomLocation();
    } else {
        return generateLocationNearPylon();
    }
}

Point2D Builder::getRandomLocation() {
    auto coordinate = Utils::getCoordinates(observation(), UNIT_TYPEID::PROTOSS_NEXUS);

    float rx = GetRandomScalar();
    float ry = GetRandomScalar();
    Point2D location = Point2D(coordinate.x + rx * 15, coordinate.y + ry * 15);
    return location;
}

Point2D Builder::generateLocationNearPylon() {
    std::vector<PowerSource> power_sources = observation()->GetPowerSources();
    const PowerSource &random_power_source = GetRandomEntry(power_sources);

    float radius = random_power_source.radius;
    float rx = GetRandomScalar();
    float ry = GetRandomScalar();
    Point2D build_location = Point2D(random_power_source.position.x + rx * radius,
                                     random_power_source.position.y + ry * radius);

    return build_location;
}

Tag Builder::generateLocationForAssimilator() {
    Units bases = observation()->GetUnits(Unit::Alliance::Self, IsTownHall());

    Tag result = 0;
    float minimum_distance = 15.0f;

    for (const auto &base : bases) {
        if (base->build_progress == 1) {
            Units geysers = observation()->GetUnits(Unit::Alliance::Neutral, IsVespeneGeyser());
            for (const auto &geyser : geysers) {
                float current_distance = Distance2D(base->pos, geyser->pos);

                if (current_distance < minimum_distance || result == 0) {
                    minimum_distance = current_distance;
                    result = geyser->tag;
                }
            }
        }
    }
    std::cout << "Build assimilator on: " << result << std::endl;
    return result;
}

bool Builder::tryBuildAssimilator(const Unit *worker) {
    Tag gayser = generateLocationForAssimilator();

    return tryBuildStructure(worker, ABILITY_ID::BUILD_ASSIMILATOR, gayser);
}

}