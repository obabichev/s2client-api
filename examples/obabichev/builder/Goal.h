//
// Created by Babichev Oleg on 25/09/2018.
//

#ifndef S2CLIENT_API_GOAL_H
#define S2CLIENT_API_GOAL_H

#import "GoalStatus.h"

namespace sc2 {

class Goal {
protected:
    bool _isActivated = false;

    bool _isCompleted = false;

    bool _isFailed = false;

public:
    Goal();

    virtual GoalStatus process() = 0;

    bool isCompleted();

    bool hasFailed();

    virtual int terminate();

    void setCompleted();

    void setFailed();

    virtual void activate();

    virtual void onActivate();

    bool isActivated();
};

}

#endif //S2CLIENT_API_GOAL_H
