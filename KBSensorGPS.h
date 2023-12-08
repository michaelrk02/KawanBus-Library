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
    KBSensorGPSDummy(void);
    ~KBSensorGPSDummy(void);

    void init(void);
    void update(void);

    void setLongitude(float value);
    float getLongitude(void);

    void setLatitude(float value);
    float getLatitude(void);

protected:
    float m_latitude;
    float m_longitude;
};

#endif
