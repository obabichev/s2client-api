//
// Created by Babichev Oleg on 25/09/2018.
//

#include "GoalComposite.h"

namespace sc2 {

GoalStatus GoalComposite::processSubgoals() {
    while (!subgoals.empty() && (subgoals.front()->isCompleted() || subgoals.front()->hasFailed())) {
        subgoals.front()->terminate();
        delete subgoals.front();
        subgoals.pop_front();
    }

    if (!subgoals.empty()) {
        GoalStatus status = subgoals.front()->process();
        if (status == GoalStatus::COMPLETED && subgoals.size() > 1) {
            return GoalStatus::ACTIVE;
        }
        return status;
    } else {
        return GoalStatus::COMPLETED;
    }
}

void GoalComposite::removeAllSubgoals() {
    for (auto &subgoal : subgoals) {
        subgoal->terminate();
        delete subgoal;
    }
    subgoals.clear();
}

GoalStatus GoalComposite::process() {
    return processSubgoals();
}

}
