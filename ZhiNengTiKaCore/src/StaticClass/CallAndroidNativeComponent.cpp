#include "CallAndroidNativeComponent.h"

#ifdef Q_OS_ANDROID

void CallAndroidNativeComponent::openUrl(const QString &url)
{
    QJniObject jUrl = QJniObject::fromString(url);
    QJniObject activity = QtAndroidPrivate::activity();

    QJniObject::callStaticMethod<void>(
        "com/LFWQSP2641/ZhiNengTiKa/IntentActivity",
        "openUrl",
        "(Ljava/lang/String;Lorg/qtproject/qt/android/bindings/QtActivity;)V",
        jUrl.object<jstring>(),
        activity.object<jobject>());
}

void CallAndroidNativeComponent::toSelfSetting()
{
    QJniObject activity = QtAndroidPrivate::activity();

    QJniObject::callStaticMethod<void>(
        "com/LFWQSP2641/ZhiNengTiKa/IntentActivity",
        "toSelfSetting",
        "(Lorg/qtproject/qt/android/bindings/QtActivity;)V",
        activity.object<jobject>());
}

QString CallAndroidNativeComponent::getCacheDir()
{
    QJniObject activity = QtAndroidPrivate::activity();
    return QJniObject::callStaticMethod<jstring>(
               "com/LFWQSP2641/ZhiNengTiKa/Util",
               "getCacheDir",
               "(Lorg/qtproject/qt/android/bindings/QtActivity;)Ljava/lang/String;",
               activity.object<jobject>())
        .toString();
}

QString CallAndroidNativeComponent::getAndroidId()
{
    QJniObject activity = QtAndroidPrivate::activity();
    return QJniObject::callStaticMethod<jstring>(
               "com/LFWQSP2641/ZhiNengTiKa/Util",
               "getAndroidId",
               "(Lorg/qtproject/qt/android/bindings/QtActivity;)Ljava/lang/String;",
               activity.object<jobject>())
        .toString();
}

QString CallAndroidNativeComponent::getDeviceName()
{
    QJniObject activity = QtAndroidPrivate::activity();
    return QJniObject::callStaticMethod<jstring>(
               "com/LFWQSP2641/ZhiNengTiKa/Util",
               "getDeviceName",
               "(Lorg/qtproject/qt/android/bindings/QtActivity;)Ljava/lang/String;",
               activity.object<jobject>())
        .toString();
}

int CallAndroidNativeComponent::getNetworkState()
{
    QJniObject activity = QtAndroidPrivate::activity();
    return QJniObject::callStaticMethod<jint>(
        "com/LFWQSP2641/ZhiNengTiKa/IntenetUtil",
        "getNetworkState",
        "(Lorg/qtproject/qt/android/bindings/QtActivity;)I",
        activity.object<jobject>());
}

void CallAndroidNativeComponent::showToast(const QString &message)
{
    QJniObject activity = QtAndroidPrivate::activity();
    QJniObject::callStaticMethod<void>(
        "com/LFWQSP2641/ZhiNengTiKa/ToastUtils",
        "show",
        "(Lorg/qtproject/qt/android/bindings/QtActivity;Ljava/lang/String;)V",
        activity.object<jobject>(),
        QJniObject::fromString(message).object<jstring>());
}

void CallAndroidNativeComponent::showToast(const QString &message, int duration)
{
    QJniObject activity = QtAndroidPrivate::activity();
    QJniObject::callStaticMethod<void>(
        "com/LFWQSP2641/ZhiNengTiKa/ToastUtils",
        "show",
        "(Lorg/qtproject/qt/android/bindings/QtActivity;Ljava/lang/String;I)V",
        activity.object<jobject>(),
        QJniObject::fromString(message).object<jstring>(),
        jint(duration));
}

bool CallAndroidNativeComponent::requestCameraPermission()
{
    auto result(QtAndroidPrivate::requestPermission(QStringLiteral("android.permission.CAMERA")));
    result.waitForFinished();
    return result.result() == QtAndroidPrivate::PermissionResult::Authorized;
}

#endif // Q_OS_ANDROID
