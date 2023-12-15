#ifndef KAWANBUS_BUS_H
#define KAWANBUS_BUS_H

#include "KBCommon.h"
#include "KBMath.h"

class KBBus : public KBDevice
{
public:
    virtual KBUID getID(void) = 0;
    virtual KBVector getPosition(void) = 0;
    virtual KBVector getDirection(void) = 0;
    virtual float getVelocity(void) = 0;
};

class KBServer;
class KBSensorGPSDummy;
class KBSensorAccelProto;

class KBBusDummy : public KBBus
{
public:
    KBBusDummy(KBServer *server, KBUID id, float proximityThreshold);
    ~KBBusDummy(void);

    void init(void);
    void update(void);

    KBUID getID(void);
    KBVector getPosition(void);
    KBVector getDirection(void);

    bool isMoving(void);
    void setMoving(bool value);

    float getVelocity(void);

protected:
    KBServer *m_server;
    KBUID m_id;
    float m_proximityThreshold;

    bool m_moving;
    unsigned long m_timer;

    KBSensorGPSDummy *m_sensorGPS;
    KBSensorAccelProto *m_sensorAccel;
    KBVector m_direction;
    int m_destination;

    int getRandomTransit(void);
};

#endif
