#ifndef VERSION_H
#define VERSION_H

#include "src/ZhiNengTiKaCore_global.h"

class ZHINENGTIKACORE_EXPORT Version
{
public:
    Version();
    explicit Version(const QString &versionString);
    Version(int major, int minor, int revision);

    QString toString() const;
    bool isEmpty() const;

    bool operator<(const Version &other) const;
    bool operator<=(const Version &other) const;
    bool operator>(const Version &other) const;
    bool operator>=(const Version &other) const;
    bool operator==(const Version &other) const;
    bool operator!=(const Version &other) const;

protected:
    QStringList versionData;
};

Q_DECLARE_METATYPE(Version);
QDebug ZHINENGTIKACORE_EXPORT operator<<(QDebug dbg, const Version &version);

#endif // VERSION_H
