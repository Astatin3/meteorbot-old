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

int main(int argc, char* argv[])
{
    try
    {
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

//        Botcraft::ConnectionClient client;
        CommandClient client(false);
        client.SetAutoRespawn(true);
//        CommandClient client(true);
//
        LOG_INFO("Starting connection process");
//
//        client.SetAutoRespawn(true);
//
//        LOG_INFO("Starting connection process");
        client.Connect(args.address, args.login);
//
//        client.RunBehaviourUntilClosed();

//        client.Disconnect();

//        return 0;

//        client.Connect(args.address, args.login);

        for (std::string line; std::getline(std::cin, line);) {
            std::cout << "Got message: "+line << std::endl;


            if(line.starts_with("chat:")){
                client.SendChatMessage(line.substr(5,line.length()));
            }else if(line.starts_with("cmd:")){
                client.SendChatCommand(line.substr(4,line.length()));
            }else if(line.starts_with("Disconnect")){
                std::cout << "Disconnected." << std::endl;
                client.Disconnect();
                return 0;
            }


        }

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