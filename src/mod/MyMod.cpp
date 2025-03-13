#include "mod/NoJoinText.h"
#include <ll/api/memory/Hook.h>
#include <mc/network/ServerNetworkHandler.h>
#include <mc/server/ServerPlayer.h>
#include "ll/api/mod/RegisterHelper.h"

namespace NoJoinText {
    NoText& NoText::getInstance() {
    static NoText instance;
    return instance;
}
LL_TYPE_INSTANCE_HOOK(
    PlayerJoinMessageHook,
    ll::memory::HookPriority::Normal,
    ServerNetworkHandler,
    &ServerNetworkHandler::onReady_ClientGeneration,
    void,
    Player&                  newPlayer,
    const NetworkIdentifier& source
) {
    if (1 == 1); {
        return;
    }
    origin(newPlayer, source);
}

LL_TYPE_INSTANCE_HOOK(
    PlayerLeftMessageHook,
    ll::memory::HookPriority::Normal,
    ServerNetworkHandler,
    &ServerNetworkHandler::_onPlayerLeft,
    void,
    ServerPlayer* player,
    bool          skipMessage
) {
    skipMessage = true; // если true - сообщение не выводит
    origin(player, skipMessage);
}

bool NoText::load() {
    getSelf().getLogger().debug("Loading...");
    // Code for loading the mod goes here.
    PlayerJoinMessageHook::hook();
    PlayerLeftMessageHook::hook();
    return true;
}

bool NoText::enable() {
    getSelf().getLogger().debug("Enabling...");
    // Code for enabling the mod goes here.
    return true;
}

bool NoText::disable() {
    getSelf().getLogger().debug("Disabling...");
    PlayerJoinMessageHook::unhook();
    PlayerLeftMessageHook::unhook();
    // Code for disabling the mod goes here.
    return true;
}

} // namespace my_mod

LL_REGISTER_MOD(NoJoinText::NoText, NoJoinText::NoText::getInstance());
