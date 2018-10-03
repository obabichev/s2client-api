//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_FOLLOWBUILDORDERGOAL_H
#define S2CLIENT_API_FOLLOWBUILDORDERGOAL_H

#include <vector>
#include "GoalComposite.h"
#include "Builder.h"

namespace sc2 {

class FollowBuildOrderGoal : public GoalComposite {
private:
    Builder *builder;
public:
    explicit FollowBuildOrderGoal(Builder *builder);
};

}

#endif //S2CLIENT_API_FOLLOWBUILDORDERGOAL_H
