#include <iostream>
#include <string>
#include <thread>
#include <chrono>

//#include "tcp/TCPServer.h"

#include "botcraft/Game/ConnectionClient.hpp"
#include "botcraft/Utilities/Logger.hpp"
#include "CommandClient.h"

struct Args
{
    bool help = false;
    std::string address = "127.0.0.1:25565";
    std::string login = "";

    int return_code = 0;
};

Args ParseCommandLine(int argc, char* argv[]);

std::vector<std::string> split(std::string text, char delim) {
    std::string line;
    std::vector<std::string> vec;
    std::stringstream ss(text);
    while(std::getline(ss, line, delim)) {
        vec.push_back(line);
    }
    return vec;
}

void runSTDINThing(CommandClient &client){
    for (std::string line; std::getline(std::cin, line);) {
        std::cout << "Got message: " + line << std::endl;


        if (line.starts_with("chat:")) {
            std::string msg = line.substr(5, line.length());
            std::cout << "Sending chat message: " + msg << std::endl;
            client.SendChatMessage(msg);
        } else if (line.starts_with("cmd:")) {
            std::string cmd = line.substr(4, line.length());
            std::cout << "Sending commnad: /" + cmd << std::endl;
            client.SendChatCommand(cmd);
        } else if (line.starts_with("Stop")){
            std::cout << "Stopped current action." << std::endl;
            client.stop();
        } else if (line.starts_with("Disconnect")) {
            std::cout << "Disconnected." << std::endl;
            client.Disconnect();
        } else if (line.starts_with("goto:")) {
            std::vector<std::string> xyz = split(line.substr(5, line.length()), ',');
            std::cout << "Moving toward: (" + xyz.at(0) + ", "
                         + xyz.at(1) + ", "
                         + xyz.at(2) + ")" << std::endl;
            client.gotocmd(std::stoi(xyz.at(0)),
                           std::stoi(xyz.at(1)),
                           std::stoi(xyz.at(2)));
        } else if (line.starts_with("startGotoSteamMode")){
            std::cout << "Started GOTO stream mode..." << std::endl;
            client.startGotoSteamMode();
        }
    }
}

int main(int argc, char* argv[]){
    try {
        // Init logging, log everything >= Info, only to console, no file
        Botcraft::Logger::GetInstance().SetLogLevel(Botcraft::LogLevel::Info);
        Botcraft::Logger::GetInstance().SetFilename("");
        // Add a name to this thread for logging
        Botcraft::Logger::GetInstance().RegisterThread("main");

        Args args;
        if (argc == 1)
        {
            LOG_WARNING("No command arguments. Using default options.");
        }
        else
        {
            args = ParseCommandLine(argc, argv);
            if (args.help)
            {
                return 0;
            }
            if (args.return_code != 0)
            {
                return args.return_code;
            }
        }

        CommandClient client(false);

        client.SetAutoRespawn(true);

        LOG_INFO("Starting connection process");

        client.Connect(args.address, args.login);

        std::thread thread(runSTDINThing, std::ref(client));

        client.RunBehaviourUntilClosed();

////        client.SetAutoRespawn(true);
//
//        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//        client.SendChatMessage("Hello, World!");
//        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
//
        client.Disconnect();


        return 0;
    }
    catch (std::exception& e){
        LOG_FATAL("Exception: " << e.what());
        return 1;
    }
    catch (...){
        LOG_FATAL("Unknown exception");
        return 2;
    }

    return 0;
}

Args ParseCommandLine(int argc, char* argv[])
{
    Args args;
    for (int i = 1; i < argc; ++i){

    }
    return args;
}