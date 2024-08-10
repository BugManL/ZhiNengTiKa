#ifndef TEMPLATESEARCHER_H
#define TEMPLATESEARCHER_H

#include "src/Logic/TemplateHandle/TemplateSummary.h"
#include "src/ZhiNengTiKaCore_global.h"

class ZHINENGTIKACORE_EXPORT TemplateSearcher : public QThread
{
    Q_OBJECT

public:
    explicit TemplateSearcher(QObject *parent = nullptr);

public slots:
    void setSearchedTemplateName(const QString &searcheredTemplateName);
    void stop();

protected:
    volatile bool toStop = false;

    QString templateName;
    void run() override;

signals:
    void searchResult(TemplateSummary templateSummary);
    void searchFinished(bool success);
    void searchStoped();
};

#endif // TEMPLATESEARCHER_H
