#include "Bbot.h"

#include <iostream>

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"

namespace sc2 {

void Bbot::OnGameStart() {
    std::cout << "Hello, World!" << std::endl;
}

void Bbot::OnStep() {
    std::cout << Observation()->GetGameLoop() << std::endl;
}

}