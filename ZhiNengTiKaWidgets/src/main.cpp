#include "src/GUI/MainWidget.h"
#include "src/Singleton/Network.h"
#include "src/Singleton/Settings.h"
#include "src/StaticClass/Global.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Global::initOnce();

    a.setWindowIcon(QIcon(QStringLiteral(":/ico/xinjiaoyuico.png")));
    a.setApplicationDisplayName(QStringLiteral("智能题卡"));

    Network::initOnce();

    auto settings(Settings::getSingletonSettings());

    QFont appFont;
    if (settings->getFontPointSize() < 1 || settings->getFont().isEmpty())
    {
        settings->setFontPointSize(a.font().pointSize());
        settings->setFont(a.font().family());
        settings->saveToFile();
    }
    else
    {
        appFont.setFamily(settings->getFont());
        appFont.setPointSize(settings->getFontPointSize());
        a.setFont(appFont);
    }

    MainWidget w;
    w.show();

    return a.exec();
}
