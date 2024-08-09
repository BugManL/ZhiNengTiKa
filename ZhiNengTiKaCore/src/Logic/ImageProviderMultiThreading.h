#ifndef IMAGEPROVIDERMULTITHREADING_H
#define IMAGEPROVIDERMULTITHREADING_H

#include "src/ZhiNengTiKaCore_global.h"

class ImageProvider;

class ZHINENGTIKACORE_EXPORT ImageProviderMultiThreading : public QObject
{
    Q_OBJECT

public:
    explicit ImageProviderMultiThreading(QObject *parent = nullptr);
    ~ImageProviderMultiThreading();

    bool getPlaceholder() const;
    void setPlaceholder(bool newPlaceholder);

    int getProgressCheckDelayMs() const;
    void setProgressCheckDelayMs(int newProgressCheckDelayMs);

public slots:
    void loadHtml(const QString &html);

protected:
    QThread thread;
    ImageProvider *imageProvider;

    bool placeholder = false;

    int progressCheckDelayMs = 500;

signals:
    void progress(int finished, int total);
    void textUpdated(const QString &str);
    void finished();
    void placeholderChanged();
    void operateImageProvider(const QString &);

    void progressCheckDelayMsChanged();

private:
    Q_PROPERTY(bool placeholder READ getPlaceholder WRITE setPlaceholder NOTIFY placeholderChanged FINAL)
    Q_PROPERTY(int progressCheckDelayMs READ getProgressCheckDelayMs WRITE setProgressCheckDelayMs NOTIFY progressCheckDelayMsChanged FINAL)
};

#endif // IMAGEPROVIDERMULTITHREADING_H
