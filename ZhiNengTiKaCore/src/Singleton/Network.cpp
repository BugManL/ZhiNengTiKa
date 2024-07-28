#include "Network.h"
Q_GLOBAL_STATIC(NetworkAccessManagerBlockable, globalManager)

NetworkAccessManagerBlockable *Network::getGlobalNetworkManager()
{
    return globalManager;
}
