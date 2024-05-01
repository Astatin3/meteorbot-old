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

}


CommandClient::~CommandClient(){}