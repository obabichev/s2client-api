//
// Created by Babichev Oleg on 03/10/2018.
//

#include <vector>
#include <iostream>

#include "MessageDispatcher.h"

namespace sc2 {

MessageDispatcher *MessageDispatcher::_instance = nullptr;

MessageDispatcher::MessageDispatcher() = default;

MessageDispatcher *MessageDispatcher::instance() {
    if (MessageDispatcher::_instance == nullptr) {
        MessageDispatcher::_instance = new MessageDispatcher();
    }
    return MessageDispatcher::_instance;
}

void MessageDispatcher::attach(TelegramType type, Observable *observer) {
    std::cout << "MessageDispatcher::attach" << std::endl;
//    observersMap.insert({type, {observer}});
    observersMap.insert({type, observer});
}

void MessageDispatcher::dispatch(TelegramType type, Telegram &telegram) {
    std::cout << "MessageDispatcher::dispatch" << std::endl;
    if (observersMap.find(type) == observersMap.end()) {
        return;
    }

//    for (auto observer : observersMap.at(type)) {
//        observer->notify(telegram);
//    }
    observersMap.at(type)->notify(telegram);
}

void MessageDispatcher::detach(TelegramType type) {
    std::cout << "MessageDispatcher::detach" << std::endl;
    observersMap.erase(type);
}

}
