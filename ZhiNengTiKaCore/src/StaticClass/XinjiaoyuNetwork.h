#pragma once

#include "src/ZhiNengTiKaCore_global.h"
class UserData;

namespace XinjiaoyuNetwork
{
extern ZHINENGTIKACORE_EXPORT QNetworkRequest setRequest(const QUrl &url, const UserData &userData);
extern ZHINENGTIKACORE_EXPORT QNetworkRequest setRequest(const QUrl &url);
extern ZHINENGTIKACORE_EXPORT QNetworkReply *getTemplateCodeData(const QString &templateCode, const UserData &userData);
extern ZHINENGTIKACORE_EXPORT QNetworkReply *getTemplateCodeData(const QString &templateCode);
extern ZHINENGTIKACORE_EXPORT QByteArray decodeTemplateReply(const QByteArray &rawdata);
extern ZHINENGTIKACORE_EXPORT QString uploadFile(const QByteArray &fileData, const QString &fileName);
extern ZHINENGTIKACORE_EXPORT QNetworkReply *uploadFileReply(const QByteArray &fileData, const QString &fileName);
extern ZHINENGTIKACORE_EXPORT QString getUploadFileReplyUrl(QNetworkReply *reply);
}; // namespace XinjiaoyuNetwork
