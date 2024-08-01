#include "ImageProvider.h"

#include "src/Singleton/Network.h"
#include "src/StaticClass/Global.h"

ImageProvider::ImageProvider(QObject *parent)
    : QObject{ parent }
{
}

QString ImageProvider::loadHtml(QString html)
{
    html = html.replace(QStringLiteral("src = '"), QStringLiteral("src='"));
    const QStringList imageSuffix({ QStringLiteral(".jpg"),
                                    QStringLiteral(".png"),
                                    QStringLiteral(".jpeg") });
    for (auto i{ html.indexOf(QStringLiteral("http")) }; i != -1; i = html.indexOf(QStringLiteral("http"), i + 1))
    {
        // NOTE 因为不知道用的是单引号还是双引号
        // NOTE 并且一定有单引号或双引号
        qsizetype endIndex;
        for (auto j{ i + 10 };; ++j)
        {
            auto str{ html.at(j) };
            if (str == QString(QStringLiteral("'")) || str == QString(QStringLiteral("\"")))
            {
                endIndex = j - 1;
                break;
            }
        }
        const auto imageUrl(html.sliced(i, endIndex - i + 1));
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
        auto reply(Network::getGlobalNetworkManager()->getByStrUrl(imageUrl));
        connect(reply, &QNetworkReply::finished, this, &ImageProvider::saveFile);
        ++totalCount;
        pathHash.insert(reply, imagePath);
        html.replace(i, endIndex - i + 1, QStringLiteral("file:///").append(imagePath));
    }
    return html;
}

void ImageProvider::resetCount()
{
    totalCount = 0;
    finishedCount = 0;
}

void ImageProvider::saveFile()
{
    auto reply(qobject_cast<QNetworkReply *>(sender()));
    const auto filePath(pathHash.take(reply));
    if (reply->error() == QNetworkReply::NoError)
    {
        const auto data(reply->readAll());
        reply->deleteLater();

        QFile file(filePath);
        if ((!file.open(QFile::ReadOnly)) || (QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5) != QCryptographicHash::hash(data, QCryptographicHash::Md5)))
        {
            file.close();
            file.open(QFile::WriteOnly);
            file.write(data);
        }
        file.close();
    }
    ++finishedCount;
    emit progress(finishedCount, totalCount);
    if (finishedCount == totalCount)
    {
        emit finished();
    }
}
