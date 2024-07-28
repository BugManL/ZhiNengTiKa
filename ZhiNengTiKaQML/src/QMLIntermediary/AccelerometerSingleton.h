#ifndef ACCELEROMETERSINGLETON_H
#define ACCELEROMETERSINGLETON_H

class AccelerometerSingleton
{
public:
    AccelerometerSingleton() = delete;
    static QAccelerometer *getAccelerometerSingleton();
};

#endif // ACCELEROMETERSINGLETON_H
