#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "NavigationBarTabWidget.h"

class SelectWidget;
class ResourceFileWidget;
class SettingWidget;

class MainWidget : public NavigationBarTabWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);

    enum TabIndex
    {
        SelectWidgetIndex = 0,
        ResourceFileWidgetIndex,
        SettingWidgetIndex
    };

protected:
    SelectWidget *selectWidget = nullptr;
    ResourceFileWidget *resourceFileWidget = nullptr;
    SettingWidget *settingWidget = nullptr;

    void closeEvent(QCloseEvent *event) override;
};

#endif // MAINWIDGET_H
