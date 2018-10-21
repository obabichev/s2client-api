#include <sc2api/sc2_api.h>

#include <bot_examples.h>
#include <sc2utils/sc2_manage_process.h>
#include "obabichev/Bbot.h"
#include "obabichev/StubBot.h"

using namespace sc2;

int main(int argc, char *argv[]) {
    Coordinator coordinator;

    if (!coordinator.LoadSettings(argc, argv)) {
        return 1;
    }

    coordinator.SetMultithreaded(true);
    coordinator.SetRealtime(false);
    StubBot stubBot;
    Bbot /*bot1,*/ bot2;

    coordinator.SetParticipants(
        {
            CreateParticipant(sc2::Race::Terran, &stubBot),
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
//                do_break = true;
            }
        }
    }

    stubBot.Control()->DumpProtoUsage();
    bot2.Control()->DumpProtoUsage();

    return 0;
}


