//
// Created by Babichev Oleg on 03/10/2018.
//

#ifndef S2CLIENT_API_MESSAGEDISPATCHER_H
#define S2CLIENT_API_MESSAGEDISPATCHER_H

#include <unordered_map>
#include <vector>

#include "TelegramType.h"
#include "Observable.h"
#include "Telegram.h"

namespace sc2 {

class MessageDispatcher {
private:
//    std::unordered_map<TelegramType, std::vector<Observable *>> observersMap;
    std::unordered_map<TelegramType, Observable *> observersMap;

    MessageDispatcher();

    static MessageDispatcher *_instance;
public:
    static MessageDispatcher *instance();

    void attach(TelegramType type, Observable *observer);

    void dispatch(TelegramType type, Telegram &telegram);

    void detach(TelegramType type);
};

}

#endif //S2CLIENT_API_MESSAGEDISPATCHER_H
