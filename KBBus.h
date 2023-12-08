#ifndef KAWANBUS_BUS_H
#define KAWANBUS_BUS_H

#include "KBMath.h"

class KBBus : public KBDevice
{
public:
    virtual KBVector getPosition(void) = 0;
    virtual KBVector getDirection(void) = 0;
    virtual float getVelocity(void) = 0;
};

class KBTransit;

class KBBusDummy : public KBBus
{
public:
    KBBusDummy(const std::vector<KBTransit *> &transits, float proximityThreshold);
    ~KBBusDummy(void);

    void init(void);
    void update(void);

    KBVector getPosition(void);
    KBVector getDirection(void);

    bool isMoving(void);
    void setMoving(bool value);

    float getVelocity(void);
    void setVelocity(float value);

protected:
    std::vector<KBTransit *> m_transits;
    float m_proximityThreshold;

    bool m_moving;
    float m_velocity;

    KBSensorGPSDummy *m_sensorGPS;
    KBVector m_direction;
    int m_destination;

    int getRandomTransit(void);
};

#endif
