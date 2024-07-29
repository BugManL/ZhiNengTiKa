#include "ZAccelerationToOpacityConverter.h"

#include <QAccelerometer>

ZAccelerationToOpacityConverter::ZAccelerationToOpacityConverter(QObject *parent)
    : QThread{ parent }
{
}

void ZAccelerationToOpacityConverter::start(Priority priority)
{
    canRun = true;
    this->QThread::start(priority);
}

void ZAccelerationToOpacityConverter::stop()
{
    canRun = false;
}

void ZAccelerationToOpacityConverter::wait()
{
    this->QThread::wait();
}

int ZAccelerationToOpacityConverter::getInterval() const
{
    return interval;
}

void ZAccelerationToOpacityConverter::setInterval(int newInterval)
{
    if (interval == newInterval)
        return;
    interval = newInterval;
    emit intervalChanged();
}

void ZAccelerationToOpacityConverter::run()
{
    QAccelerometer accelerometer;
    while (canRun)
    {
        if (this->interval > 0)
            QThread::msleep(this->interval);
        const auto reading(accelerometer.reading());
        if (reading != nullptr)
        {
            const auto opacity(convertZAccelerationToOpacity(reading->z()));
            emit opacityChanged(opacity);
        }
        else
        {
            ++tryCount;
            if (tryCount > maxTryCount)
            {
                qDebug() << Q_FUNC_INFO << QStringLiteral("reading != nullptr & tryCount > maxTryCount, stop thread");
                canRun = false;
                tryCount = 0;
                emit opacityChanged(0.5);
            }
        }
    }
}

qreal ZAccelerationToOpacityConverter::convertZAccelerationToOpacity(qreal zAcceleration)
{
    const auto transformZ(qAbs(zAcceleration) / 10);
#if 0
    return 4 * transformZ * transformZ * transformZ - 6 * transformZ * transformZ + 3 * transformZ;
#else
    return transformZ - 0.1;
#endif
}
