#ifndef KAWANBUS_SERVER_H
#define KAWANBUS_SERVER_H

#include "KBCommon.h"
#include "KBMath.h"

class KBTransit;
class KBBus;

class KBServer
{
public:
    virtual std::vector<KBTransit *> getTransits(void) = 0;
    virtual std::vector<KBBus *> getBuses(void) = 0;

    virtual void sendPosition(KBVector v) = 0;
    virtual void sendDirection(KBVector v) = 0;
    virtual void sendSpeed(float s) = 0;
    virtual void sendTransitInRange(KBUID id) = 0;
    virtual void sendTransitInProximity(KBUID id) = 0;
    virtual void sendEstimates(int time, int distance) = 0;

    virtual KBUID getTrackID(void) = 0;
};

#endif
