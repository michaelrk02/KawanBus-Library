#include "KBSensorGPS.h"

#include "KBTransit.h"

KBTransitDummy::KBTransitDummy(void)
{
    m_sensorGPS = new KBSensorGPSDummy();
}

KBTransitDummy::~KBTransitDummy(void)
{
    delete m_sensorGPS;
}

void KBTransitDummy::init(void)
{
}

void KBTransitDummy::update(void)
{
    m_sensorGPS->update();
}

KBVector KBTransitDummy::getPosition(void)
{
    KBVector pos;
    pos.x = m_sensorGPS->getLongitude();
    pos.y = m_sensorGPS->getLatitude();
    return pos;
}

void KBTransitDummy::setPosition(KBVector value)
{
    m_sensorGPS->setLongitude(value.x);
    m_sensorGPS->setLatitude(value.y);
}
