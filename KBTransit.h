#ifndef KAWANBUS_TRANSIT_H
#define KAWANBUS_TRANSIT_H

#include "KBMath.h"

class KBTransit : public KBDevice
{
public:
    virtual KBVector getPosition(void) = 0;
};

class KBTransitDummy : public KBTransit
{
public:
    KBTransitDummy(void);
    ~KBTransitDummy(void);

    void init(void);
    void update(void);

    KBVector getPosition(void);
    void setPosition(KBVector value);

protected:
    KBSensorGPSDummy *m_sensorGPS;
};

#endif
