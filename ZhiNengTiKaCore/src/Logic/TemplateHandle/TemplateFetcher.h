#ifndef TEMPLATEFETCHER_H
#define TEMPLATEFETCHER_H

#include "TemplateAnalysis.h"
#include "src/ZhiNengTiKaCore_global.h"

class ZHINENGTIKACORE_EXPORT TemplateFetcher : public QObject
{
    Q_OBJECT

public:
    explicit TemplateFetcher(QObject *parent = nullptr);
public slots:
    void handleTemplateRequest(const TemplateSummary &templateSummary);
    void handleTemplateRequestByCode(const QString &templateCode);
    void handleTemplateRequestNetwork(const TemplateSummary &templateSummary);
    void handleTemplateRequestByCodeNetwork(const QString &templateCode);

protected:
    QHash<QNetworkReply *, TemplateAnalysis> hash;
protected slots:
    void onHandleTemplateReplyFinished();
signals:
    void obtainTemplateFromNetwork();
    void templateAnalysisReady(const TemplateAnalysis &templateAnalysis, const QByteArray &rawData = QByteArray());
    void error(const QString &msg);
};

#endif // TEMPLATEFETCHER_H
