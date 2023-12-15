#ifndef KAWANBUS_TRANSIT_H
#define KAWANBUS_TRANSIT_H

#include <set>

#include "KBCommon.h"
#include "KBMath.h"

class KBTransit : public KBDevice
{
public:
    virtual KBUID getID(void) = 0;
    virtual KBVector getPosition(void) = 0;
    virtual KBUID getNearestBusID(void) = 0;
    virtual float getNearestBusDistance(void) = 0;
    virtual float getNearestBusETA(void) = 0;
};

class KBServer;

class KBTransitDummy : public KBTransit
{
public:
    KBTransitDummy(KBServer *server, KBUID id, float rangeThreshold, float proximityThreshold);
    ~KBTransitDummy(void);

    void init(void);
    void update(void);

    KBUID getID(void);

    KBVector getPosition(void);
    void setPosition(KBVector value);

    KBUID getNearestBusID(void);
    float getNearestBusDistance(void);
    float getNearestBusETA(void);

protected:
    KBServer *m_server;
    KBUID m_id;
    float m_rangeThreshold;
    float m_proximityThreshold;

    KBSensorGPSDummy *m_sensorGPS;
    std::set<KBUID> m_inRange;
    std::set<KBUID> m_inProximity;
};

#endif
