#include "ImageProviderMultiThreading.h"

#include "src/Logic/ImageProvider.h"

ImageProviderMultiThreading::ImageProviderMultiThreading(QObject *parent)
    : QObject{ parent },
      imageProvider(new ImageProvider)
{
    imageProvider->moveToThread(&thread);

    connect(imageProvider, &ImageProvider::progress, this, &ImageProviderMultiThreading::progress);
    connect(imageProvider, &ImageProvider::textUpdated, this, &ImageProviderMultiThreading::textUpdated);
    connect(imageProvider, &ImageProvider::finished, this, &ImageProviderMultiThreading::finished);
    connect(imageProvider, &ImageProvider::placeholderChanged, this, &ImageProviderMultiThreading::placeholderChanged);

    connect(this, &ImageProviderMultiThreading::operateImageProvider, imageProvider, &ImageProvider::loadHtml);

    connect(&thread, &QThread::finished, imageProvider, &ImageProvider::deleteLater);
}

ImageProviderMultiThreading::~ImageProviderMultiThreading()
{
    thread.quit();
    thread.wait();
}

void ImageProviderMultiThreading::loadHtml(const QString &html)
{
    thread.start();
    emit operateImageProvider(html);
}

bool ImageProviderMultiThreading::getPlaceholder() const
{
    return placeholder;
}

void ImageProviderMultiThreading::setPlaceholder(bool newPlaceholder)
{
    if (placeholder == newPlaceholder)
        return;
    placeholder = newPlaceholder;
    imageProvider->setPlaceholder(newPlaceholder);
    emit placeholderChanged();
}

int ImageProviderMultiThreading::getProgressCheckDelayMs() const
{
    return progressCheckDelayMs;
}

void ImageProviderMultiThreading::setProgressCheckDelayMs(int newProgressCheckDelayMs)
{
    if (progressCheckDelayMs == newProgressCheckDelayMs)
        return;
    progressCheckDelayMs = newProgressCheckDelayMs;
    imageProvider->setProgressCheckDelayMs(newProgressCheckDelayMs);
    emit progressCheckDelayMsChanged();
}
