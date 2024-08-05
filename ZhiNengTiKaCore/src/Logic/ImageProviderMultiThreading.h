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

public slots:
    void loadHtml(const QString &html);

protected:
    QThread thread;
    ImageProvider *imageProvider;

    bool placeholder = false;

signals:
    void progress(int finished, int total);
    void textUpdated(const QString &str);
    void finished();
    void placeholderChanged();
    void operateImageProvider(const QString &);

private:
    Q_PROPERTY(bool placeholder READ getPlaceholder WRITE setPlaceholder NOTIFY placeholderChanged FINAL)
};

#endif // IMAGEPROVIDERMULTITHREADING_H
