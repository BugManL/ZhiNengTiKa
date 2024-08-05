#include "Settings.h"

#include "src/Logic/UserData.h"
#include "src/StaticClass/Global.h"

Q_GLOBAL_STATIC(Settings, singletonSettings)

Settings::Settings(QObject *parent)
    : QObject{ parent },
      accountManager(new AccountManager(this))
{
    QByteArray fileData;
    QFile file{ Global::configPath().append(QStringLiteral("/setting.json")) };
    if (file.exists())
    {
        file.open(QFile::ReadOnly);
        fileData = file.readAll();
    }
    else
    {
        file.open(QFile::NewOnly);
    }
    file.close();

    const auto settingJsonObject{ QJsonDocument::fromJson(fileData).object() };
    const auto accountsJsonArray{ settingJsonObject.value("accounts").toArray() };

    for (const auto &i : accountsJsonArray)
    {
        const auto jsonObject{ i.toObject() };
        // 只有authorization不能空(虽然别的空了也不行...)
        if (!jsonObject.contains(QStringLiteral("authorization")))
        {
            continue;
        }
        accountManager->userDatasAppend(UserData(
            jsonObject.value(QStringLiteral("accessToken")).toString().toUtf8(),
            jsonObject.value(QStringLiteral("authorization")).toString().toUtf8(),
            jsonObject.value(QStringLiteral("clientSession")).toString(QUuid::createUuid().toString(QUuid::WithoutBraces)).toUtf8(),
            jsonObject.value(QStringLiteral("studentId")).toString().toUtf8(),
            QJsonDocument::fromJson(QByteArray::fromBase64(jsonObject.value(QStringLiteral("detailData")).toString().toUtf8())).object(),
            jsonObject.value(QStringLiteral("password")).toString().toUtf8(),
            jsonObject.value(QStringLiteral("schoolId")).toString().toUtf8(),
            jsonObject.value(QStringLiteral("username")).toString().toUtf8()));
    }

    fontPointSize = settingJsonObject.value(QStringLiteral("fontPointSize")).toInt();
    font = settingJsonObject.value(QStringLiteral("font")).toString();
    qmlStyle = settingJsonObject.value(QStringLiteral("qmlStyle")).toString();

    animeImageUrl = settingJsonObject.value(QStringLiteral("animeImageUrl")).toString();
}

AccountManager *Settings::getAccountManager() const
{
    return accountManager;
}

QString Settings::getAnimeImageUrl() const
{
    return animeImageUrl;
}

void Settings::setAnimeImageUrl(const QString &newAnimeImageUrl)
{
    if (animeImageUrl == newAnimeImageUrl)
        return;
    animeImageUrl = newAnimeImageUrl;
    emit animeImageUrlChanged();
}

void Settings::resetAnimeImageUrl()
{
    setAnimeImageUrl(animeImageUrlList.at(0).second);
}

QList<QPair<QString, QString>> Settings::getAnimeImageUrlList() const
{
    return animeImageUrlList;
}

Settings *Settings::getSingletonSettings()
{
    return singletonSettings;
}

int Settings::getFontPointSize() const
{
    return fontPointSize;
}

void Settings::setFontPointSize(int newFontPointSize)
{
    if (fontPointSize == newFontPointSize)
        return;
    fontPointSize = newFontPointSize;
    emit fontPointSizeChanged();
}

void Settings::resetFontPointSize()
{
    setFontPointSize(0);
}

QString Settings::getFont() const
{
    return font;
}

void Settings::setFont(const QString &newFont)
{
    if (font == newFont)
        return;
    font = newFont;
    emit fontChanged();
}

void Settings::resetFont()
{
    setFont(QString{});
}

QString Settings::getQmlStyle() const
{
    return qmlStyle;
}

void Settings::setQmlStyle(const QString &newQmlStyle)
{
    if (qmlStyle == newQmlStyle)
        return;
    qmlStyle = newQmlStyle;
    emit qmlStyleChanged();
}

void Settings::resetQmlStyle()
{
    setQmlStyle(QString{});
}

void Settings::saveToFile() const
{
    QJsonObject settingJsonObject;
    QJsonArray accountsJsonArray;
    for (const auto &i : accountManager->getUserDatas())
    {
        QJsonObject jsonObject;
        jsonObject.insert(QStringLiteral("accessToken"), QString(i.getAccessToken()));
        jsonObject.insert(QStringLiteral("authorization"), QString(i.getAuthorization()));
        jsonObject.insert(QStringLiteral("clientSession"), QString(i.getClientSession()));
        jsonObject.insert(QStringLiteral("password"), QString(i.getPassword()));
        jsonObject.insert(QStringLiteral("schoolId"), QString(i.getSchoolId()));
        jsonObject.insert(QStringLiteral("detailData"), QString(QJsonDocument(i.getDetailDataJsonObject()).toJson(QJsonDocument::Compact).toBase64()));
        jsonObject.insert(QStringLiteral("studentId"), QString(i.getStudentId()));
        jsonObject.insert(QStringLiteral("username"), QString(i.getUsername()));

        accountsJsonArray.append(jsonObject);
    }
    settingJsonObject.insert(QStringLiteral("accounts"), accountsJsonArray);

    settingJsonObject.insert(QStringLiteral("fontPointSize"), fontPointSize);
    settingJsonObject.insert(QStringLiteral("font"), font);

    settingJsonObject.insert(QStringLiteral("qmlStyle"), qmlStyle);

    settingJsonObject.insert(QStringLiteral("animeImageUrl"), animeImageUrl);

    QFile file{ Global::configPath().append(QStringLiteral("/setting.json")) };
    file.open(QFile::WriteOnly);
    file.write(QJsonDocument(settingJsonObject).toJson(QJsonDocument::Compact));
    file.close();
}
