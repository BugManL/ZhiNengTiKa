#include "MultipleSubjectsTemplateListView.h"

#include "TemplateListView.h"
#include "src/Singleton/MultipleSubjectsTemplateListModelListSingleton.h"

MultipleSubjectsTemplateListView::MultipleSubjectsTemplateListView(QWidget *parent)
    : QWidget{ parent },
      mainLayout(new QVBoxLayout(this)),
      multipleSubjectsTabBar(new QTabBar(this)),
      templateListView(new TemplateListView(this))
{
    const QStringList subjects({ QStringLiteral("用户历史"),
                                 QStringLiteral("语文"), QStringLiteral("数学"),
                                 QStringLiteral("英语"), QStringLiteral("物理"),
                                 QStringLiteral("化学"), QStringLiteral("生物") });
    for (const auto &subjectName : subjects)
    {
        multipleSubjectsTabBar->addTab(subjectName);
    }
    multipleSubjectsTabBar->setDrawBase(false);
    multipleSubjectsTabBar->setElideMode(Qt::ElideRight);

    templateListView->setTemplateListModel(MultipleSubjectsTemplateListModelListSingleton::getMultipleSubjectsTemplateListModelList()->at(0));

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(multipleSubjectsTabBar);
    mainLayout->addWidget(templateListView);

    connect(multipleSubjectsTabBar, &QTabBar::currentChanged, this, [this](int index)
            {
        if(index > -1)
        {
            templateListView->setTemplateListModel(MultipleSubjectsTemplateListModelListSingleton::getMultipleSubjectsTemplateListModelList()->at(index));
            currentSubject = index;
        } });
    connect(templateListView, &TemplateListView::templateNameClicked, this, &MultipleSubjectsTemplateListView::templateNameClicked);
}

void MultipleSubjectsTemplateListView::addNewTemplate(const TemplateSummary &templateSummary)
{
    MultipleSubjectsTemplateListModelListSingleton::getMultipleSubjectsTemplateListModelList()->addNewTemplate(templateSummary);
    if (currentSubject == MultipleSubjectsTemplateListModelList::Subjects::UserHistory)
    {
        templateListView->setCurrentIndex(templateListView->indexAt(QPoint(0, 0)));
    }
}

TemplateSummary MultipleSubjectsTemplateListView::getCurrentTemplateSummary()
{
    return this->templateListView->getCurrentTemplateSummary();
}

TemplateListView *MultipleSubjectsTemplateListView::getCurrentTemplateListView() const
{
    return templateListView;
}

int MultipleSubjectsTemplateListView::getCurrentSubject() const
{
    return currentSubject;
}
