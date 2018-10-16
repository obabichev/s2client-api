//
// Created by Babichev Oleg on 06/10/2018.
//

#ifndef S2CLIENT_API_OBSERVABLE_H
#define S2CLIENT_API_OBSERVABLE_H

#include "Telegram.h"

namespace sc2 {

class Observable {
public:
    virtual void notify(Telegram& telegram) = 0;
};

}

#endif //S2CLIENT_API_OBSERVABLE_H
