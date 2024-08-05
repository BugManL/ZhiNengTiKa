include($$PWD/../precompile_header/precompile_header.pri)
include($$PWD/../ZhiNengTiKaCommon.pri)

QT += widgets gui quick quickcontrols2

TEMPLATE = app

DEFINES += ZHINENGTIKAQML

HEADERS += \
    $$PWD/src/QMLIntermediary/AnimeImageProvider.h \
    $$PWD/src/QMLIntermediary/QMLUtils.h \
    $$PWD/src/QMLIntermediary/SettingOperator.h \

SOURCES += \
    $$PWD/src/QMLIntermediary/AnimeImageProvider.cpp \
    $$PWD/src/QMLIntermediary/QMLUtils.cpp \
    $$PWD/src/QMLIntermediary/SettingOperator.cpp \
    $$PWD/src/mainQML.cpp

RESOURCES += \
    $$PWD/Resource/qml.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/release/ -lZhiNengTiKaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/debug/ -lZhiNengTiKaCore
else:unix: LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/ -lZhiNengTiKaCore_$${QT_ARCH}

INCLUDEPATH += $$PWD/../ZhiNengTiKaCore
DEPENDPATH += $$PWD/../ZhiNengTiKaCore

android {
include($$PWD/../3rd/android_openssl/openssl.pri)
ANDROID_PACKAGE_SOURCE_DIR = $$PWD/../android
DISTFILES += \
    $$PWD/../android/AndroidManifest.xml \
    $$PWD/../android/build.gradle \
    $$PWD/../android/gradle.properties \
    $$PWD/../android/gradle/wrapper/gradle-wrapper.jar \
    $$PWD/../android/gradle/wrapper/gradle-wrapper.properties \
    $$PWD/../android/gradlew \
    $$PWD/../android/gradlew.bat \
    $$PWD/../android/res/drawable-hdpi/icon.png \
    $$PWD/../android/res/drawable-ldpi/icon.png \
    $$PWD/../android/res/drawable-mdpi/icon.png \
    $$PWD/../android/res/drawable-xhdpi/icon.png \
    $$PWD/../android/res/drawable-xxhdpi/icon.png \
    $$PWD/../android/res/drawable-xxxhdpi/icon.png \
    $$PWD/../android/res/values/libs.xml \
    $$PWD/../android/res/xml/provider_paths.xml \
    $$PWD/../android/src/com/LFWQSP2641/zhinengtika/CallNativeComponent.java \
    $$PWD/../android/src/com/LFWQSP2641/zhinengtika/IntenetUtil.java \
    $$PWD/../android/src/com/LFWQSP2641/zhinengtika/IntentActivity.java \
    $$PWD/../android/src/com/LFWQSP2641/zhinengtika/ToastUtils.java \
    $$PWD/../android/src/com/LFWQSP2641/zhinengtika/Util.java
}
