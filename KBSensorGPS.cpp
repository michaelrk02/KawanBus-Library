#include "KBMath.h"

#include "KBSensorGPS.h"

KBSensorGPSDummy::KBSensorGPSDummy(void)
{
    m_longitude = 0.0f;
    m_latitude = 0.0f;
}

KBSensorGPSDummy::~KBSensorGPSDummy(void)
{
}

void KBSensorGPSDummy::init(void)
{
}

void KBSensorGPSDummy::update(void)
{
}

void KBSensorGPSDummy::setLongitude(float value)
{
    m_longitude = value;
}

float KBSensorGPSDummy::getLongitude(void)
{
    return m_longitude;
}

void KBSensorGPSDummy::setLatitude(float value)
{
    m_latitude = value;
}

float KBSensorGPSDummy::getLatitude(void)
{
    return m_latitude;
}
