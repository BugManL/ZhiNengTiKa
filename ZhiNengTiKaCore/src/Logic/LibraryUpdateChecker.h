#ifndef LIBRARYUPDATECHECKER_H
#define LIBRARYUPDATECHECKER_H

#include "UpdateChecker.h"

class LibraryUpdateChecker : public UpdateChecker
{
    Q_OBJECT
public:
    explicit LibraryUpdateChecker(QObject *parent = nullptr);
    explicit LibraryUpdateChecker(const Version &currentVersion, QObject *parent = nullptr);
public slots:
    void installNewestVersion() override;
protected:
    QString getDomain() const override;
    QString getSaveFilePath() const override;

    const QString domain;
    const QString saveFilePath;
private:
    Q_PROPERTY(QString domain READ getDomain CONSTANT FINAL)
    Q_PROPERTY(QString saveFilePath READ getSaveFilePath CONSTANT FINAL)
};

#endif // LIBRARYUPDATECHECKER_H
