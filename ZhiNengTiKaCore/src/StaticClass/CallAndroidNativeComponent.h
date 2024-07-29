#ifndef CALLANDROIDNATIVECOMPONENT_H
#define CALLANDROIDNATIVECOMPONENT_H

#ifdef Q_OS_ANDROID

#include "src/ZhiNengTiKaCore_global.h"

namespace CallAndroidNativeComponent
{
void ZHINENGTIKACORE_EXPORT openUrl(const QString &url);
void ZHINENGTIKACORE_EXPORT toSelfSetting();
QString ZHINENGTIKACORE_EXPORT getCacheDir();
QString ZHINENGTIKACORE_EXPORT getAndroidId();
QString ZHINENGTIKACORE_EXPORT getDeviceName();
int ZHINENGTIKACORE_EXPORT getNetworkState();
void ZHINENGTIKACORE_EXPORT showToast(const QString &message);
void ZHINENGTIKACORE_EXPORT showToast(const QString &message, int duration);
}; // namespace CallAndroidNativeComponent

#endif // Q_OS_ANDROID

#endif // CALLANDROIDNATIVECOMPONENT_H
