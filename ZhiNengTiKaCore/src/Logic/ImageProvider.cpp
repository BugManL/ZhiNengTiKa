#include "ImageProvider.h"

#include "src/Singleton/Network.h"
#include "src/StaticClass/Global.h"

ImageProvider::ImageProvider(QObject *parent)
    : QObject{ parent }
{
}

QString ImageProvider::loadHtml(const QString &html)
{
    currentUuid = QUuid::createUuid();
    resetCount();
    rawData = html;
    rawData.replace(QStringLiteral("\""), QStringLiteral("'"));
    rawData.replace(QStringLiteral("src = '"), QStringLiteral("src='"));
    const QStringList imageSuffix({ QStringLiteral(".jpg"),
                                    QStringLiteral(".png"),
                                    QStringLiteral(".jpeg") });
    for (auto i{ rawData.indexOf(QStringLiteral("http")) }; i != -1; i = rawData.indexOf(QStringLiteral("http"), i + 1))
    {
        const auto endIndex(rawData.indexOf(QStringLiteral("'"), i + 10) - 1);
        const auto imageUrl(rawData.sliced(i, endIndex - i + 1));
        const auto pointIndex(imageUrl.lastIndexOf("."));
        if (pointIndex == -1)
        {
            continue;
        }
        const auto suffix{ imageUrl.last(imageUrl.size() - pointIndex).toLower() };
        if (!imageSuffix.contains(suffix))
        {
            continue;
        }
        const QString imageName(QCryptographicHash::hash(imageUrl.toUtf8(), QCryptographicHash::Sha1).toHex() + suffix);
        const QString imagePath(Global::dataPath().append(QStringLiteral("/Image/")).append(imageName));
        const auto placeholderName(QStringLiteral("qrc:/ico/img/loading.svg?PLACEHOLDERNAMEBEGIN").append(QUuid::createUuid().toString(QUuid::WithoutBraces)).append(QStringLiteral("PLACEHOLDERNAMEEND")));
        auto info = new ImageFileInfo{ currentUuid, imagePath, placeholderName };
        auto reply(Network::getGlobalNetworkManager()->getByStrUrl(imageUrl));
        pathHash.insert(reply, info);
        connect(reply, &QNetworkReply::finished, this, &ImageProvider::saveFile);
        ++totalCount;
        if (placeholder)
        {
            rawData.replace(i, endIndex - i + 1, placeholderName);
        }
        else
        {
            rawData.replace(i, endIndex - i + 1, QStringLiteral("file:///").append(imagePath));
        }
    }
    return rawData;
}

bool ImageProvider::getPlaceholder() const
{
    return placeholder;
}

void ImageProvider::setPlaceholder(bool newPlaceholder)
{
    if (placeholder == newPlaceholder)
        return;
    placeholder = newPlaceholder;
    emit placeholderChanged();
}

void ImageProvider::resetCount()
{
    totalCount = 0;
    finishedCount = 0;
}

void ImageProvider::saveFile()
{
    auto reply(qobject_cast<QNetworkReply *>(sender()));
    const auto info(pathHash.take(reply));
    if (reply->error() == QNetworkReply::NoError)
    {
        const auto data(reply->readAll());
        reply->deleteLater();

        QFile file(info->imagePath);
        if (!(file.open(QFile::ReadOnly) && (QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5) == QCryptographicHash::hash(data, QCryptographicHash::Md5))))
        {
            file.close();
            file.open(QFile::WriteOnly);
            file.write(data);
        }
        file.close();
    }
    if (currentUuid != info->batch)
    {
        delete info;
        return;
    }
    if (placeholder)
    {
        // TODO 优化, 多次查找, 过于耗时
        rawData.replace(info->placeholderName, QStringLiteral("file:///").append(info->imagePath));
        emit textUpdated(rawData);
    }
    delete info;
    ++finishedCount;
    emit progress(finishedCount, totalCount);
    if (finishedCount == totalCount)
    {
        emit finished();
    }
}
