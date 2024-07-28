#pragma once

#include "src/Logic/NetworkAccessManagerBlockable.h"
#include "src/ZhiNengTiKaCore_global.h"

class ZHINENGTIKACORE_EXPORT Network
{
public:
    static void initOnce();
    static void resetNetworkManager();
    static NetworkAccessManagerBlockable *getGlobalNetworkManager();

private:
    Network() = default;
    static NetworkAccessManagerBlockable *globalManager;
};
