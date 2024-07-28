#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "UserData.h"
#include "src/ZhiNengTiKaCore_global.h"

class ZHINENGTIKACORE_EXPORT AccountManager : public QObject
{
    Q_OBJECT

public:
    explicit AccountManager(QObject *parent = nullptr);

    UserData getPublicUserData() const;

    Q_INVOKABLE UserData getCurrentUserData() const;
    Q_INVOKABLE bool isLoggedin() const;
    Q_INVOKABLE QVariant getDescriptionOfUserDatas() const;

    QList<UserData> getUserDatas() const;

public slots:
    void login(const QString &username, const QString &password);
    void loginUtf8(const QByteArray &username, const QByteArray &password);
    void relogin(qsizetype index = 0);
    void checkCurrentAccountValid();
    void initPublicUserData();

    void toFirst(qsizetype i);
    void logout();

    void userDatasAppend(const UserData &newUserData);

protected:
    QNetworkReply *getLoginReply(const QString &username, const QString &password);
    QNetworkReply *getLoginReplyUtf8(const QByteArray &username, const QByteArray &password);
    QHash<QNetworkReply *, QList<QByteArray>> loginHash;
    QHash<QNetworkReply *, UserData> reloginHash;

    UserData publicUserData;
    QList<UserData> userDatas;

protected slots:
    void onLoginReplyFinished();
    void onReloginReplyFinished();
    void onCheckCurrentAccountValidReplyFinished();
    void onPublicUserDataReplyFinished();

signals:
    void loginFinished(bool success, UserData object);
    void reloginFinished(bool success, UserData object);
    void checkCurrentAccountValidFinished(bool valid);
    void initPublicUserDataFinished(UserData object);
    void error(const QString &msg);

private:
    Q_PROPERTY(UserData publicUserData READ getPublicUserData CONSTANT FINAL)
    Q_PROPERTY(QList<UserData> userDatas READ getUserDatas CONSTANT FINAL)
};

#endif // ACCOUNTMANAGER_H
