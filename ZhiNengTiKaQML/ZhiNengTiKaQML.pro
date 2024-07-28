VERSION = 3.0.2
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

include($$PWD/../precompile_header/precompile_header.pri)
include($$PWD/../ZhiNengTiKaCommon.pri)

QT += widgets gui quick quickcontrols2 webenginequick sensors

TEMPLATE = app

DEFINES += ZHINENGTIKAQML

HEADERS += \
    $$PWD/src/QMLIntermediary/AccelerometerSingleton.h \
    $$PWD/src/QMLIntermediary/AnimeImageProvider.h \
    $$PWD/src/QMLIntermediary/MultipleSubjectsTemplateListModelListSingleton.h \
    $$PWD/src/QMLIntermediary/QMLUtils.h \
    $$PWD/src/QMLIntermediary/SettingOperator.h \
    $$PWD/src/QMLIntermediary/ZAccelerationToOpacityConverter.h

SOURCES += \
    $$PWD/src/QMLIntermediary/AccelerometerSingleton.cpp \
    $$PWD/src/QMLIntermediary/AnimeImageProvider.cpp \
    $$PWD/src/QMLIntermediary/MultipleSubjectsTemplateListModelListSingleton.cpp \
    $$PWD/src/QMLIntermediary/QMLUtils.cpp \
    $$PWD/src/QMLIntermediary/SettingOperator.cpp \
    $$PWD/src/QMLIntermediary/ZAccelerationToOpacityConverter.cpp \
    $$PWD/src/mainQML.cpp

RESOURCES += \
    $$PWD/Resource/qml.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/release/ -lZhiNengTiKaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/debug/ -lZhiNengTiKaCore
else:unix: LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/ -lZhiNengTiKaCore

INCLUDEPATH += $$PWD/../ZhiNengTiKaCore
DEPENDPATH += $$PWD/../ZhiNengTiKaCore
