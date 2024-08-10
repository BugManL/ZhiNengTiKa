#include "TemplateAnswerData.h"

TemplateAnswerData::TemplateAnswerData(const QString &count, const QByteArray &questionId, const bool isAChoiceQuestion, const QBitArray &answer)
    : count(count),
      questionId(questionId),
      choiceQuestion(isAChoiceQuestion),
      answer(answer)
{
    const auto trueCount{ answer.count(true) };
    if (trueCount > 1)
    {
        multipleChoiceQuestion = true;
    }
}

TemplateAnswerData::TemplateAnswerData(const TemplateAnswerData &others)
    : count(others.getCount()),
      questionId(others.getQuestionId()),
      choiceQuestion(others.isChoiceQuestion()),
      answer(others.getAnswer()),
      multipleChoiceQuestion(others.isMultipleChoiceQuestion()) {}

TemplateAnswerData TemplateAnswerData::operator=(const TemplateAnswerData &others) const
{
    return TemplateAnswerData(others);
}

QString TemplateAnswerData::getCount() const
{
    return count;
}

QByteArray TemplateAnswerData::getQuestionId() const
{
    return questionId;
}

bool TemplateAnswerData::isChoiceQuestion() const
{
    return choiceQuestion;
}

QBitArray TemplateAnswerData::getAnswer() const
{
    return answer;
}

bool TemplateAnswerData::isMultipleChoiceQuestion() const
{
    return multipleChoiceQuestion;
}

QList<TemplateAnswerData> TemplateAnswerData::getChildQuestionList() const
{
    return childQuestionList;
}
