
#include <getopt.h>
#include <iostream>

#include <mclib/common/Common.h>
#include <mclib/core/Client.h>
#include <mclib/util/Forge.h>
#include <mclib/util/Hash.h>
#include <mclib/util/Utility.h>
#include <mclib/util/VersionFetcher.h>

#include "Logger.h"

namespace {

const std::string server("127.0.0.1");
u16 port = 25565;
const std::string username("testplayer");
const std::string password("");
const bool useProfileToken = false;

}  // namespace

int run(mc::protocol::Version versions, mc::util::ForgeHandler &forge);
void parse_arguments(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    parse_arguments(argc, argv);
    mc::util::VersionFetcher versionFetcher(server, port);

    std::cout << "Fetching version" << std::endl;

    auto version = versionFetcher.GetVersion();

    mc::block::BlockRegistry::GetInstance()->RegisterVanillaBlocks(version);

    std::cout << "Connecting with version " << mc::protocol::to_string(version)
              << std::endl;
    return run(version, versionFetcher.GetForge());
}

int run(mc::protocol::Version version, mc::util::ForgeHandler &forge) {
    mc::protocol::packets::PacketDispatcher dispatcher;
    mc::core::Client client(&dispatcher, version);

    forge.SetConnection(client.GetConnection());

    client.GetPlayerController()->SetHandleFall(true);
    client.GetConnection()
        ->GetSettings()
        .SetMainHand(mc::MainHand::Right)
        .SetViewDistance(16);

    example::Logger logger(&client, &dispatcher);

    try {
        std::cout << "Logging in." << std::endl;

        mc::core::AuthToken token;

        if (useProfileToken && mc::util::GetProfileToken(username, &token)) {
            std::cout << "Using profile token." << std::endl;
            client.Login(server, port, username, token,
                         mc::core::UpdateMethod::Block);
        } else {
            client.Login(server, port, username, password,
                         mc::core::UpdateMethod::Block);
        }
    } catch (std::exception &e) {
        std::wcout << e.what() << std::endl;
        return 1;
    }

    return 0;
}

void parse_arguments(int argc, char *argv[]) {
    if (argc == 2) {
        port = strtoul(argv[1], nullptr, 10);
    }
}