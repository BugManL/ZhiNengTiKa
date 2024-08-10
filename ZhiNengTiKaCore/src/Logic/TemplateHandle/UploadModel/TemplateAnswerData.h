#ifndef TEMPLATEANSWERDATA_H
#define TEMPLATEANSWERDATA_H

#include "src/ZhiNengTiKaCore_global.h"

class TemplateData;
class TemplateAnalysis;

class ZHINENGTIKACORE_EXPORT TemplateAnswerData
{
    Q_GADGET
    friend TemplateData;
    friend TemplateAnalysis;

public:
    TemplateAnswerData() = default;
    TemplateAnswerData(const QString &count, const QByteArray &questionId, const bool isAChoiceQuestion, const QBitArray &answer = QBitArray());
    TemplateAnswerData(const TemplateAnswerData &others);

    TemplateAnswerData operator=(const TemplateAnswerData &others) const;

    QString getCount() const;

    QByteArray getQuestionId() const;

    bool isChoiceQuestion() const;

    QBitArray getAnswer() const;

    bool isMultipleChoiceQuestion() const;

    QList<TemplateAnswerData> getChildQuestionList() const;

protected:
    QString count;
    QByteArray questionId;
    bool choiceQuestion;
    QBitArray answer;
    bool multipleChoiceQuestion = false;

    QList<TemplateAnswerData> childQuestionList;

private:
    Q_PROPERTY(QString count READ getCount CONSTANT FINAL)
    Q_PROPERTY(QByteArray questionId READ getQuestionId CONSTANT FINAL)
    Q_PROPERTY(bool choiceQuestion READ isChoiceQuestion CONSTANT FINAL)
    Q_PROPERTY(QBitArray answer READ getAnswer CONSTANT FINAL)
    Q_PROPERTY(bool multipleChoiceQuestion READ isMultipleChoiceQuestion CONSTANT FINAL)
    Q_PROPERTY(QList<TemplateAnswerData> childQuestionList READ getChildQuestionList CONSTANT FINAL)
};

#endif // TEMPLATEANSWERDATA_H
