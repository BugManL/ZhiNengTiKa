#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include "src/ZhiNengTiKaCore_global.h"

// (Widgets)提供显示网络图片支持
// (Quick)加快加载速度
class ZHINENGTIKACORE_EXPORT ImageProvider : public QObject
{
    Q_OBJECT

public:
    explicit ImageProvider(QObject *parent = nullptr);
    Q_INVOKABLE QString loadHtml(QString html);
public slots:
    void resetCount();

protected:
    int totalCount = 0;
    int finishedCount = 0;
    QHash<QNetworkReply *, QString> pathHash;
protected slots:
    void saveFile();
signals:
    void progress(int finished, int total);
    void finished();
};

#endif // IMAGEPROVIDER_H
