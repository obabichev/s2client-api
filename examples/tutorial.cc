#include <sc2api/sc2_api.h>

#include <bot_examples.h>
#include <sc2utils/sc2_manage_process.h>
#include "obabichev/Bbot.h"

using namespace sc2;

int main(int argc, char *argv[]) {
    Coordinator coordinator;

    if (!coordinator.LoadSettings(argc, argv)) {
        return 1;
    }

    coordinator.SetMultithreaded(true);
    ProtossMultiplayerBot bot1;
//    Bbot bot2;
    Bbot bot2;

    coordinator.SetParticipants(
        {
            CreateParticipant(sc2::Race::Protoss, &bot1),
            CreateParticipant(sc2::Race::Protoss, &bot2)
        });

    coordinator.LaunchStarcraft();


    bool do_break = false;
    while (!do_break) {
        if (!coordinator.StartGame(sc2::kMapBelShirVestigeLE)) {
            break;
        }
        while (coordinator.Update() && !do_break) {
            if (sc2::PollKeyPress()) {
                do_break = true;
            }
        }
    }

    bot1.Control()->DumpProtoUsage();
    bot2.Control()->DumpProtoUsage();

    return 0;
}


