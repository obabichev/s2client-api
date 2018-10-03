//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_GOAL_H
#define S2CLIENT_API_GOAL_H

#import "GoalStatus.h"

namespace sc2 {

class Goal {
protected:
    bool _isCompleted = false;

public:
    Goal();

    virtual GoalStatus process() = 0;

    bool isCompleted();

    bool hasFailed();

    int terminate();

    void setCompleted(bool isCompleted);
};

}

#endif //S2CLIENT_API_GOAL_H
