#include "TemplateAnswerData.h"

TemplateAnswerData::TemplateAnswerData(TemplateAnswerData *parentItem)
    : parentItem(parentItem)
{
}

TemplateAnswerData::TemplateAnswerData(const QString &count, const QByteArray &questionId, const bool isAChoiceQuestion, int choiceQuestionCount, QString &&answer, TemplateAnswerData *parentItem)
    : count(count),
      questionId(questionId),
      choiceQuestion(isAChoiceQuestion),
      choiceQuestionCount(choiceQuestionCount),
      answer(answer),
      parentItem(parentItem)
{
    if (answer.size() > 1)
    {
        multipleChoiceQuestion = true;
    }
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

bool TemplateAnswerData::isMultipleChoiceQuestion() const
{
    return multipleChoiceQuestion;
}

QList<TemplateAnswerData *> TemplateAnswerData::getChildQuestionList() const
{
    return childQuestionList;
}

int TemplateAnswerData::getChoiceQuestionCount() const
{
    return choiceQuestionCount;
}

QString TemplateAnswerData::getAnswer() const
{
    return answer;
}

int TemplateAnswerData::childCount() const
{
    return childQuestionList.size();
}

int TemplateAnswerData::row() const
{
    if (parentItem == nullptr)
        return 0;
    return parentItem->childQuestionList.indexOf(this);
}

TemplateAnswerData *TemplateAnswerData::child(int row) const
{
    return row >= 0 && row < childCount() ? childQuestionList.at(row) : nullptr;
}

void TemplateAnswerData::addChild(TemplateAnswerData &&child)
{
    auto templateAnswerData(new TemplateAnswerData(std::move(child)));
    childQuestionList.append(templateAnswerData);
}

TemplateAnswerData *TemplateAnswerData::getParentItem() const
{
    return parentItem;
}
