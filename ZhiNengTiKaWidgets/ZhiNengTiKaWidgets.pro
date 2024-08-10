include($$PWD/../precompile_header/precompile_header.pri)
include($$PWD/../ZhiNengTiKaCommon.pri)

QT       += widgets gui multimedia multimediawidgets

TEMPLATE = app

DEFINES += ZHINENGTIKAWIDGETS

HEADERS += \
    $$PWD/src/GUI/AnswerAndAnalysisWidget.h \
    $$PWD/src/GUI/ClickableLabel.hpp \
    $$PWD/src/GUI/MainWidget.h \
    $$PWD/src/GUI/MultipleSubjectsTemplateListView.h \
    $$PWD/src/GUI/NavigationBarTabWidget.h \
    $$PWD/src/GUI/PixmapLabel.h \
    $$PWD/src/GUI/PlusSignLabel.h \
    $$PWD/src/GUI/QRCodeScannerWidget.h \
    $$PWD/src/GUI/QuestionWidget.h \
    $$PWD/src/GUI/ResourceFileWidget.h \
    $$PWD/src/GUI/SearchWidget.h \
    $$PWD/src/GUI/SelectWidget.h \
    $$PWD/src/GUI/SettingWidget.h \
    $$PWD/src/GUI/TemplateDetailWidget.h \
    $$PWD/src/GUI/TemplateListView.h \
    $$PWD/src/GUI/WebViewWidget.h

SOURCES += \
    $$PWD/src/GUI/AnswerAndAnalysisWidget.cpp \
    $$PWD/src/GUI/MainWidget.cpp \
    $$PWD/src/GUI/MultipleSubjectsTemplateListView.cpp \
    $$PWD/src/GUI/NavigationBarTabWidget.cpp \
    $$PWD/src/GUI/PixmapLabel.cpp \
    $$PWD/src/GUI/PlusSignLabel.cpp \
    $$PWD/src/GUI/QRCodeScannerWidget.cpp \
    $$PWD/src/GUI/QuestionWidget.cpp \
    $$PWD/src/GUI/ResourceFileWidget.cpp \
    $$PWD/src/GUI/SearchWidget.cpp \
    $$PWD/src/GUI/SelectWidget.cpp \
    $$PWD/src/GUI/SettingWidget.cpp \
    $$PWD/src/GUI/TemplateDetailWidget.cpp \
    $$PWD/src/GUI/TemplateListView.cpp \
    $$PWD/src/GUI/WebViewWidget.cpp \
    $$PWD/src/main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/release/ -lZhiNengTiKaCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/debug/ -lZhiNengTiKaCore
else:unix: LIBS += -L$$OUT_PWD/../ZhiNengTiKaCore/ -lZhiNengTiKaCore_$${QT_ARCH}

INCLUDEPATH += $$PWD/../ZhiNengTiKaCore
DEPENDPATH += $$PWD/../ZhiNengTiKaCore
