VERSION = 3.0.2
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

include($$PWD/../precompile_header/precompile_header.pri)
include($$PWD/../ZhiNengTiKaCommon.pri)

TEMPLATE = lib

QT += core network multimedia

#DEFINES += LIMITED

DEFINES += ZHINENGTIKACORE_LIBRARY

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

CONFIG(debug, debug|release) {
    win32 {
        LIBS += -L$$PWD/../3rd_build/build/qt_aes/Windows_MSVC2019_64bit/Debug -lqt_aes
        LIBS += -L$$PWD/../3rd_build/build/zxing/Windows_MSVC2019_64bit/Debug -lzxing
    }
    android {
        LIBS += -L$$PWD/../3rd_build/build/qt_aes/Android_arm64_v8a/Debug -lqt_aes_arm64-v8a
        LIBS += -L$$PWD/../3rd_build/build/zxing/Android_arm64_v8a/Debug -lzxing_arm64-v8a
    }
} else {
    win32 {
        LIBS += -L$$PWD/../3rd_build/build/qt_aes/Windows_MSVC2019_64bit/Release -lqt_aes
        LIBS += -L$$PWD/../3rd_build/build/zxing/Windows_MSVC2019_64bit/Release -lzxing
    }
    android {
        LIBS += -L$$PWD/../3rd_build/build/qt_aes/Android_arm64_v8a/Release -lqt_aes_arm64-v8a
        LIBS += -L$$PWD/../3rd_build/build/zxing/Android_arm64_v8a/Release -lzxing_arm64-v8a
    }
}

INCLUDEPATH += $$PWD/../3rd/zxing-cpp/core/src

HEADERS += \
    $$PWD/src/Logic/AccountManager.h \
    $$PWD/src/Logic/AnnouncementManager.h \
    $$PWD/src/Logic/AnnouncementModel.h \
    $$PWD/src/Logic/AnswerDetailData.hpp \
    $$PWD/src/Logic/FileTreeItem.h \
    $$PWD/src/Logic/FileTreeModel.h \
    $$PWD/src/Logic/ImageProvider.h \
    $$PWD/src/Logic/MultipleSubjectsTemplateListModelList.h \
    $$PWD/src/Logic/NetworkAccessManagerBlockable.h \
    $$PWD/src/Logic/QRCodeReader.h \
    $$PWD/src/Logic/QRCodeScanner.h \
    $$PWD/src/Logic/ResourceFileFetcher.h \
    $$PWD/src/Logic/ResourceFileModel.h \
    $$PWD/src/Logic/TemplateAnalysis.h \
    $$PWD/src/Logic/TemplateFetcher.h \
    $$PWD/src/Logic/TemplateListModel.h \
    $$PWD/src/Logic/TemplateSearcher.h \
    $$PWD/src/Logic/TemplateSummary.h \
    $$PWD/src/Logic/UserData.h \
    $$PWD/src/Logic/Version.h \
    $$PWD/src/Singleton/Network.h \
    $$PWD/src/Singleton/Settings.h \
    $$PWD/src/StaticClass/CallAndroidNativeComponent.h \
    $$PWD/src/StaticClass/Global.h \
    $$PWD/src/StaticClass/XinjiaoyuEncryptioner.h \
    $$PWD/src/StaticClass/XinjiaoyuNetwork.h \
    $$PWD/src/ZhiNengTiKaCore_global.h \
    $$PWD/src/ZhiNengTiKaCoreVersion.h \
    $$PWD/src/ZxingCpp/ZXingPosition.h \
    $$PWD/src/ZxingCpp/ZXingReader.h \
    $$PWD/src/ZxingCpp/ZXingResult.h

SOURCES += \
    $$PWD/src/Logic/AccountManager.cpp \
    $$PWD/src/Logic/AnnouncementManager.cpp \
    $$PWD/src/Logic/AnnouncementModel.cpp \
    $$PWD/src/Logic/FileTreeItem.cpp \
    $$PWD/src/Logic/FileTreeModel.cpp \
    $$PWD/src/Logic/ImageProvider.cpp \
    $$PWD/src/Logic/QRCodeReader.cpp \
    $$PWD/src/Logic/QRCodeScanner.cpp \
    $$PWD/src/Logic/MultipleSubjectsTemplateListModelList.cpp \
    $$PWD/src/Logic/NetworkAccessManagerBlockable.cpp \
    $$PWD/src/Logic/ResourceFileFetcher.cpp \
    $$PWD/src/Logic/ResourceFileModel.cpp \
    $$PWD/src/Logic/TemplateAnalysis.cpp \
    $$PWD/src/Logic/TemplateFetcher.cpp \
    $$PWD/src/Logic/TemplateListModel.cpp \
    $$PWD/src/Logic/TemplateSearcher.cpp \
    $$PWD/src/Logic/TemplateSummary.cpp \
    $$PWD/src/Logic/UserData.cpp \
    $$PWD/src/Logic/Version.cpp \
    $$PWD/src/Singleton/Network.cpp \
    $$PWD/src/Singleton/Settings.cpp \
    $$PWD/src/StaticClass/CallAndroidNativeComponent.cpp \
    $$PWD/src/StaticClass/Global.cpp \
    $$PWD/src/StaticClass/XinjiaoyuEncryptioner.cpp \
    $$PWD/src/StaticClass/XinjiaoyuNetwork.cpp \
    $$PWD/src/ZhiNengTiKaCoreVersion.cpp \
    $$PWD/src/ZxingCpp/ZXingPosition.cpp \
    $$PWD/src/ZxingCpp/ZXingReader.cpp \
    $$PWD/src/ZxingCpp/ZXingResult.cpp

RESOURCES += \
    $$PWD/Resource/Resource.qrc \
    $$PWD/Resource/Template.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rd_build/Qt-AES/release/ -lqt_aes
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rd_build/Qt-AES/debug/ -lqt_aes
else:unix: LIBS += -L$$OUT_PWD/../3rd_build/Qt-AES/ -lqt_aes

INCLUDEPATH += $$PWD/../3rd_build/Qt-AES
DEPENDPATH += $$PWD/../3rd_build/Qt-AES

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/Qt-AES/release/libqt_aes.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/Qt-AES/debug/libqt_aes.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/Qt-AES/release/qt_aes.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/Qt-AES/debug/qt_aes.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/Qt-AES/libqt_aes.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../3rd_build/zxing-cpp/release/ -lzxing
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../3rd_build/zxing-cpp/debug/ -lzxing
else:unix: LIBS += -L$$OUT_PWD/../3rd_build/zxing-cpp/ -lzxing

INCLUDEPATH += $$PWD/../3rd_build/zxing-cpp
DEPENDPATH += $$PWD/../3rd_build/zxing-cpp

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/zxing-cpp/release/libzxing.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/zxing-cpp/debug/libzxing.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/zxing-cpp/release/zxing.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/zxing-cpp/debug/zxing.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../3rd_build/zxing-cpp/libzxing.a
