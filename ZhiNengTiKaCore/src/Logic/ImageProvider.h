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
    Q_INVOKABLE QString loadHtml(const QString &html);

    bool getPlaceholder() const;
    void setPlaceholder(bool newPlaceholder);

    int getProgressCheckDelayMs() const;
    void setProgressCheckDelayMs(int newProgressCheckDelayMs);
public slots:
    void emitProgress();

protected:
    struct ImageFileInfo
    {
        const QUuid batch;
        const QString imagePath;
        const QString placeholderName;
    };

    bool placeholder = false;
    int totalCount = 0;
    int finishedCount = 0;

    int progressCheckDelayMs = 500;

    QUuid currentUuid;
    QHash<QNetworkReply *, ImageFileInfo *> pathHash;
    QString rawData;

    QNetworkAccessManager *manager;
    QTimer *timer;

protected slots:
    void onReplyFinished();
    void resetCount();

signals:
    void progress(int finished, int total);
    void textUpdated(const QString &str);
    void finished();
    void placeholderChanged();

    void progressCheckDelayMsChanged();

private:
    Q_PROPERTY(bool placeholder READ getPlaceholder WRITE setPlaceholder NOTIFY placeholderChanged FINAL)
    Q_PROPERTY(int progressCheckDelayMs READ getProgressCheckDelayMs WRITE setProgressCheckDelayMs NOTIFY progressCheckDelayMsChanged FINAL)
};

#endif // IMAGEPROVIDER_H
