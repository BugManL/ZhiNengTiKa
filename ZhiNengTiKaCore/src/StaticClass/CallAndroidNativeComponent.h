#ifndef CALLANDROIDNATIVECOMPONENT_H
#define CALLANDROIDNATIVECOMPONENT_H

#ifdef Q_OS_ANDROID

#include "src/ZhiNengTiKaCore_global.h"

namespace CallAndroidNativeComponent
{
extern void ZHINENGTIKACORE_EXPORT openUrl(const QString &url);
extern void ZHINENGTIKACORE_EXPORT toSelfSetting();
extern QString ZHINENGTIKACORE_EXPORT getCacheDir();
extern QString ZHINENGTIKACORE_EXPORT getAndroidId();
extern QString ZHINENGTIKACORE_EXPORT getDeviceName();
extern int ZHINENGTIKACORE_EXPORT getNetworkState();
extern void ZHINENGTIKACORE_EXPORT showToast(const QString &message);
extern void ZHINENGTIKACORE_EXPORT showToast(const QString &message, int duration);
extern bool ZHINENGTIKACORE_EXPORT requestCameraPermission();
extern bool ZHINENGTIKACORE_EXPORT requestStoragePermission();
}; // namespace CallAndroidNativeComponent

#endif // Q_OS_ANDROID

#endif // CALLANDROIDNATIVECOMPONENT_H
