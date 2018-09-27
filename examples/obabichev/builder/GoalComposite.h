//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_GOALCOMPOSITE_H
#define S2CLIENT_API_GOALCOMPOSITE_H

#include <deque>
#include "Goal.h"

namespace sc2 {

class GoalComposite : public Goal {
protected:
    std::deque<Goal *> subgoals;

public:
    GoalStatus processSubgoals();

    void removeAllSubgoals();

    GoalStatus process() override;
};

}

#endif //S2CLIENT_API_GOALCOMPOSITE_H
