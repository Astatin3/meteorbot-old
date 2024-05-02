#pragma once

#include "botcraft/Game/Vector3.hpp"
#include "botcraft/AI/TemplatedBehaviourClient.hpp"

/// @brief Example of a class where we inherit
/// TemplatedBehaviourClient<T>, with this class as parameter.
/// We can then use Behaviour Trees with this class as
/// context, and do our stuff. We also override on Handle function
class CommandClient : public Botcraft::TemplatedBehaviourClient<CommandClient>
{
public:
    CommandClient(const bool use_renderer_);
    ~CommandClient();

    void gotopos(int x, int y, int z);
    void gotocmd(int x, int y, int z);

    void startGotoSteamMode();

    void stop();
};