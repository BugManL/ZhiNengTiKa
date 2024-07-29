#include "QMLUtils.h"

#include "src/StaticClass/Global.h"

#ifdef Q_OS_ANDROID
#include "src/StaticClass/CallAndroidNativeComponent.h"
#endif

QMLUtils::QMLUtils(QObject *parent)
    : QObject{ parent }
{
}

QColor QMLUtils::generateRandomColor()
{
    int red = QRandomGenerator::global()->bounded(256);
    int green = QRandomGenerator::global()->bounded(256);
    int blue = QRandomGenerator::global()->bounded(256);

    return QColor(red, green, blue);
}

QColor QMLUtils::generateRandomBrightColor()
{
    int red = QRandomGenerator::global()->bounded(128, 256);
    int green = QRandomGenerator::global()->bounded(128, 256);
    int blue = QRandomGenerator::global()->bounded(128, 256);

    return QColor(red, green, blue);
}

QString QMLUtils::getResourceFilePath()
{
    return Global::dataPath().append(QStringLiteral("/Resource"));
}

bool QMLUtils::openLocalFile(const QString &path)
{
    return QDesktopServices::openUrl(QUrl::fromLocalFile(path));
}

bool QMLUtils::requestCameraPermission()
{
#ifdef Q_OS_ANDROID
    return CallAndroidNativeComponent::requestCameraPermission();
#endif
    return true;
}
