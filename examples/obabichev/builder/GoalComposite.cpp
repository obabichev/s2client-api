#include "GoalComposite.h"

namespace sc2 {

GoalStatus GoalComposite::processSubgoals() {
    while (!subgoals.empty() && (subgoals.front()->isCompleted() || subgoals.front()->hasFailed())) {
        subgoals.front()->terminate();
        delete subgoals.front();
        subgoals.pop_front();
    }

    if (!subgoals.empty()) {
        auto subgoal = subgoals.front();
        if (!subgoal->isActivated()) {
            subgoal->activate();
        }
        GoalStatus status = subgoal->process();
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
