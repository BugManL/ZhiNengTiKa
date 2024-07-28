#include "AccelerometerSingleton.h"

Q_GLOBAL_STATIC(QAccelerometer, accelerometerSingleton)

QAccelerometer *AccelerometerSingleton::getAccelerometerSingleton()
{
    return accelerometerSingleton;
}
