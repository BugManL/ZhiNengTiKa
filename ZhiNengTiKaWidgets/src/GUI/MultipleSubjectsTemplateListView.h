#ifndef MULTIPLESUBJECTSTEMPLATELISTVIEW_H
#define MULTIPLESUBJECTSTEMPLATELISTVIEW_H

#include "src/Logic/TemplateSummary.h"

class TemplateListView;

class MultipleSubjectsTemplateListView : public QWidget
{
    Q_OBJECT

public:
    explicit MultipleSubjectsTemplateListView(QWidget *parent = nullptr);
    void addNewTemplate(const TemplateSummary &templateSummary);

    TemplateSummary getCurrentTemplateSummary();

    TemplateListView *getCurrentTemplateListView() const;

    int getCurrentSubject() const;

protected:
    QVBoxLayout *mainLayout;
    QTabBar *multipleSubjectsTabBar;
    TemplateListView *templateListView;

    int currentSubject = 0;

signals:
    void templateNameClicked(const TemplateSummary &templateSummary);

private:
    Q_PROPERTY(int currentSubject READ getCurrentSubject CONSTANT FINAL)
};

#endif // MULTIPLESUBJECTSTEMPLATELISTVIEW_H
