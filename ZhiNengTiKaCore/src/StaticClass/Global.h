#pragma once

#include "src/ZhiNengTiKaCore_global.h"

// 全局变量以及不足以成一个类的成员都会放到这
namespace Global
{
extern ZHINENGTIKACORE_EXPORT QString appConfigPath;
extern ZHINENGTIKACORE_EXPORT QString appDataPath;
extern ZHINENGTIKACORE_EXPORT QString appTempPath;

extern ZHINENGTIKACORE_EXPORT void initOnce();

extern ZHINENGTIKACORE_EXPORT QString configPath();
extern ZHINENGTIKACORE_EXPORT QString dataPath();
extern ZHINENGTIKACORE_EXPORT QString tempPath();

extern ZHINENGTIKACORE_EXPORT bool deleteDir(const QString &path);
extern ZHINENGTIKACORE_EXPORT qint64 getDirSize(const QString &filePath);
extern ZHINENGTIKACORE_EXPORT void webImageDownloadToLocal(QString &webStr);
}; // namespace Global
