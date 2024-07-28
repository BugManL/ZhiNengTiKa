#pragma once

#include "Qt-AES/qaesencryption.h"
#include "zxing-cpp/ZXingReader.h"
#include "zxing-cpp/ZXingResult.h"

#ifdef QT_CORE_LIB
#include <QtCore>
#endif

#ifdef QT_CONCURRENT_LIB
#include <QtConcurrent>
#endif

#ifdef QT_GUI_LIB
#include <QtGui>
#endif

#ifdef QT_WIDGETS_LIB
#include <QtWidgets>
#endif

#ifdef QT_MULTIMEDIA_LIB
#include <QtMultimedia>
#endif

#ifdef QT_NETWORK_LIB
#include <QtNetwork>
#endif

#ifdef QT_XML_LIB
#include <QtXml>
#endif

#ifdef QT_QML_LIB
#include <QtQml>
#endif

#ifdef QT_QUICK_LIB
#include <QtQuick>
#endif

#ifdef QT_SQL_LIB
#include <QtSql>
#endif

#ifdef QT_PRINTSUPPORT_LIB
#include <QtPrintSupport>
#endif

#ifdef Q_OS_ANDROID
#include <QtCore/private/qandroidextras_p.h>
#endif
