#include "MainWidget.h"

#include "ResourceFileWidget.h"
#include "SelectWidget.h"
#include "SettingWidget.h"
#include "src/Singleton/Settings.h"

MainWidget::MainWidget(QWidget *parent)
    : NavigationBarTabWidget{ parent },
      selectWidget(new SelectWidget(this)),
      resourceFileWidget(new ResourceFileWidget(this)),
      settingWidget(new SettingWidget(this))
{
    this->addTab(selectWidget, QStringLiteral("题卡"));
    this->addTab(resourceFileWidget, QStringLiteral("学案"));
    this->addTabWithScrollArea(settingWidget, QStringLiteral("设置"));

    connect(this, &QTabWidget::currentChanged, [this](int index)
            {
                switch (index)
                {
                case TabIndex::ResourceFileWidgetIndex:
                    resourceFileWidget->init();
                    break;
                case TabIndex::SettingWidgetIndex:
                    settingWidget->refreshTempSize();
                    break;
                default:
                    break;
                } });
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    Settings::getSingletonSettings()->saveToFile();
    NavigationBarTabWidget::closeEvent(event);
    event->accept();
}
