#include "ImageProvider.h"

#include "src/StaticClass/Global.h"

ImageProvider::ImageProvider(QObject *parent)
    : QObject{ parent },
      manager(new QNetworkAccessManager(this)),
      timer(new QTimer(this))
{
    timer->setSingleShot(false);
    timer->setInterval(progressCheckDelayMs);
    connect(timer, &QTimer::timeout, this, &ImageProvider::emitProgress);
}

QString ImageProvider::loadHtml(const QString &html)
{
    currentUuid = QUuid::createUuid();
    resetCount();
    rawData = html;
    rawData.replace(QStringLiteral("\""), QStringLiteral("'"));
    rawData.replace(QStringLiteral("src = '"), QStringLiteral("src='"));
    const QStringList imageSuffixs({ QStringLiteral(".jpg"),
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
        if (!imageSuffixs.contains(suffix))
        {
            continue;
        }
        const auto imageUrlSha1Hex(QCryptographicHash::hash(imageUrl.toUtf8(), QCryptographicHash::Sha1).toHex());
        const QString imagePath(Global::tempPath().append(QStringLiteral("/Image/")).append(imageUrlSha1Hex).append(suffix));
        const auto placeholderName(QStringLiteral("qrc:/ico/img/loading.svg?PLACEHOLDERNAMEBEGIN").append(imageUrlSha1Hex).append(QStringLiteral("PLACEHOLDERNAMEEND")));
        auto info = new ImageFileInfo{ currentUuid, imagePath, placeholderName };
        auto reply(manager->get(QNetworkRequest(imageUrl)));
        pathHash.insert(reply, info);
        connect(reply, &QNetworkReply::finished, this, &ImageProvider::onReplyFinished);
        ++totalCount;
        if ((!placeholder) || QFile(imagePath).exists())
        {
            rawData.replace(i, endIndex - i + 1, QStringLiteral("file:///").append(imagePath));
        }
        else
        {
            rawData.replace(i, endIndex - i + 1, placeholderName);
        }
    }
    emit progress(finishedCount, totalCount);
    emit textUpdated(rawData);
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

int ImageProvider::getProgressCheckDelayMs() const
{
    return progressCheckDelayMs;
}

void ImageProvider::setProgressCheckDelayMs(int newProgressCheckDelayMs)
{
    if (progressCheckDelayMs == newProgressCheckDelayMs)
        return;
    progressCheckDelayMs = newProgressCheckDelayMs;
    emit progressCheckDelayMsChanged();
}

void ImageProvider::emitProgress()
{
    emit progress(finishedCount, totalCount);
    emit textUpdated(rawData);
}

void ImageProvider::resetCount()
{
    totalCount = 0;
    finishedCount = 0;
}

void ImageProvider::onReplyFinished()
{
    // 获取发送信号的QNetworkReply对象
    auto reply = qobject_cast<QNetworkReply *>(sender());

    // 从哈希表中获取对应的信息
    const auto info = pathHash.take(reply);
    bool needReplacePlaceholder = false;

    // 检查网络请求是否成功
    if (reply->error() == QNetworkReply::NoError)
    {
        // 读取返回的数据
        const auto data = reply->readAll();
        reply->deleteLater();

        QFile file(info->imagePath);
        needReplacePlaceholder = placeholder && (!file.exists());

        // 打开文件并检查哈希值是否匹配
        if (!(file.open(QFile::ReadOnly) &&
              (QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5) ==
               QCryptographicHash::hash(data, QCryptographicHash::Md5))))
        {
            // 如果哈希值不匹配，重写文件
            file.close();
            file.open(QFile::WriteOnly);
            file.write(data);
        }
        file.close();
    }

    // 如果当前处理的UUID与批次信息不一致，删除info对象并返回
    if (currentUuid != info->batch)
    {
        delete info;
        return;
    }

    // 替换占位符并更新文本
    if (needReplacePlaceholder)
    {
        // TODO 优化, 多次查找, 过于耗时
        rawData.replace(info->placeholderName, QStringLiteral("file:///").append(info->imagePath));
    }

    // 删除info对象并更新进度
    delete info;
    ++finishedCount;

    // 如果所有任务完成，发出finished信号
    if (finishedCount == totalCount)
    {
        timer->stop();
        emitProgress();
        emit finished();
    }
    else if (!timer->isActive())
    {
        timer->start();
    }
}
