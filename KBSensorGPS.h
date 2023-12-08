#ifndef KAWANBUS_SENSOR_GPS_H
#define KAWANBUS_SENSOR_GPS_H

#include <vector>

#include "KBDevice.h"
#include "KBMath.h"

class KBSensorGPS : public KBDevice
{
public:
    virtual float getLongitude(void) = 0;
    virtual float getLatitude(void) = 0;
};

class KBSensorGPSDummy : public KBSensorGPS
{
public:
    KBSensorGPSDummy(const std::vector<KBVector> &nodes, float nodeThreshold);
    ~KBSensorGPSDummy(void);

    void init(void);
    void update(void);
    float getLongitude(void);
    float getLatitude(void);

    bool isMoving(void);
    void setMoving(bool value);

    float getVelocity(void);
    void setVelocity(float value);

protected:
    std::vector<KBVector> m_nodes;
    float m_nodeThreshold;

    bool m_moving;
    float m_velocity;

    int m_destination;
    float m_latitude;
    float m_longitude;

    int getRandomNode(void);
};

#endif
