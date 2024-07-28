#pragma once

#include "src/ZhiNengTiKaCore_global.h"

namespace XinjiaoyuEncryptioner
{
extern ZHINENGTIKACORE_EXPORT QByteArray xinjiaoyuEncryption(const QByteArray &rawText);
extern ZHINENGTIKACORE_EXPORT QByteArray xinjiaoyuDecryption(const QByteArray &rawText);
extern ZHINENGTIKACORE_EXPORT QByteArray getXinjiaoyuMD5(const QByteArray &tValue, const QByteArray &clientSessionValue);

extern ZHINENGTIKACORE_EXPORT QAESEncryption encryptioner;
extern ZHINENGTIKACORE_EXPORT const QByteArray xinjiaoyuKey;
}; // namespace XinjiaoyuEncryptioner
