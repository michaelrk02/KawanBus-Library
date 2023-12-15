#ifndef KAWANBUS_SENSOR_ACCEL_H
#define KAWANBUS_SENSOR_ACCEL_H

#include "KBDevice.h"

#ifndef KB_PROTO_ACCEL_PIN
#define KB_PROTO_ACCEL_PIN D7
#endif

class KBSensorAccel : public KBDevice
{
public:
    virtual float getVelocity(void) = 0;
};

class KBSensorAccelProto : public KBSensorAccel
{
public:
    KBSensorAccelProto(int pin, float wheelRadius);

    void init(void);
    void update(void);
    float getVelocity(void);

protected:
    int m_pin;
    float m_wheelRadius;

    int m_state;
    unsigned long m_lastCycle;
    float m_velocity;
};

#endif
