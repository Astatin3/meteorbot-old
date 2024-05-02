#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

#include "botcraft/Game/World/World.hpp"
#include "botcraft/Game/Entities/EntityManager.hpp"
#include "botcraft/Game/Entities/LocalPlayer.hpp"
#include "botcraft/Network/NetworkManager.hpp"

#include "botcraft/AI/BehaviourTree.hpp"
#include "botcraft/AI/Tasks/AllTasks.hpp"

#include "CommandClient.h"

using namespace Botcraft;
using namespace ProtocolCraft;

CommandClient::CommandClient(const bool use_renderer_) : TemplatedBehaviourClient<CommandClient>(use_renderer_){
    std::cout << "Bot started!" << std::endl;
}

CommandClient::~CommandClient(){}

bool running = false;
bool gotoCmdStream = false;

void CommandClient::gotopos(int x, int y, int z){
    Position target_position = Position(x, y, z);
    float speed_multiplier = 2.0f;;

    auto tree = Builder<CommandClient>("goto tree")
            .sequence()
                    // Perform the pathfinding in a Selector,
                    // so it exits as soon as one leaf
                    // returns success
            .selector()
                    // The next three lines do exactly the same,
                    // they're only here to show the different
                    // possibilities to create a leaf. Note that
                    // only the lambda solution can use default
                    // parameters values
            .leaf("go to lambda", [=](CommandClient& c) { return GoTo(c, target_position, 0, 0, 0, true, false, speed_multiplier); })
            .leaf("go to function", GoTo, target_position, 0, 0, 0, true, false, speed_multiplier)
            .leaf("go to std::bind", std::bind(GoTo, std::placeholders::_1, target_position, 0, 0, 0, true, false, speed_multiplier))
                    // If goto fails, say something in chat
            .leaf(Say, "Pathfinding failed :(")
            .end()
                    // Switch back to empty behaviour
            .leaf([](CommandClient& c) { c.SetBehaviourTree(nullptr); return Status::Success; })
            .end();

    SetBehaviourTree(tree);
}

void CommandClient::gotocmd(int x, int y, int z){
    if(running && !gotoCmdStream){
        std::cout << "Already running a task." << std::endl;
        running = true;
        return;
    }

    gotopos(x,y,z);
}

void CommandClient::startGotoSteamMode(){
    if(running){
        std::cout << "Already running a task." << std::endl;
        running = true;
        return;
    }

    running = true;
    gotoCmdStream = true;
}

void CommandClient::stop(){
    if(running){
        std::cout << "Stopped..." << std::endl;
        SetBehaviourTree(nullptr);
        gotoCmdStream = false;
        running = false;
    }else{
        std::cout << "No task is running..." << std::endl;
    }
}