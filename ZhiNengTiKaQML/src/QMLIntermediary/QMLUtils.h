#ifndef QMLUTILS_H
#define QMLUTILS_H

class QMLUtils : public QObject
{
    Q_OBJECT

public:
    explicit QMLUtils(QObject *parent = nullptr);
    Q_INVOKABLE QColor generateRandomColor();
    Q_INVOKABLE QColor generateRandomPastelColor();
    Q_INVOKABLE QString getResourceFilePath();
    Q_INVOKABLE bool openLocalFile(const QString &path);
    Q_INVOKABLE bool requestCameraPermission();
public slots:
signals:
};

#endif // QMLUTILS_H
