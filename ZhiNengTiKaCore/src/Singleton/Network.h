#pragma once

#include "src/Logic/NetworkAccessManagerBlockable.h"
#include "src/ZhiNengTiKaCore_global.h"

class ZHINENGTIKACORE_EXPORT Network
{
public:
    Network() = delete;
    static NetworkAccessManagerBlockable *getGlobalNetworkManager();
};
