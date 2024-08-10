#ifndef TEMPLATEDETAILWIDGET_H
#define TEMPLATEDETAILWIDGET_H

#include "NavigationBarTabWidget.h"
#include "src/Logic/TemplateHandle/TemplateAnalysis.h"

class AnswerAndAnalysisWidget;
class QuestionWidget;
class UploadWidget;

class TemplateDetailWidget : public NavigationBarTabWidget
{
    Q_OBJECT

public:
    explicit TemplateDetailWidget(const TemplateAnalysis &templateAnalysis, QWidget *parent = nullptr);

    enum TabIndex
    {
        AnswerAndAnalysisWidgetIndex = 0,
        QuestionWidgetIndex = 1
    };

public slots:
    void setTemplateAnalysis(const TemplateAnalysis &templateAnalysis);

protected:
    AnswerAndAnalysisWidget *answerAndAnalysisWidget;
    QuestionWidget *questionWidget;

    void showEvent(QShowEvent *event) override;
};

#endif // TEMPLATEDETAILWIDGET_H
