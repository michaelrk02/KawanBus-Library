#include "KBSensorGPS.h"
#include "KBTransit.h"

#include "KBBus.h"

KBBusDummy::KBBusDummy(const std::vector<KBTransit *> &nodes, float proximityThreshold)
{
    m_transits = nodes;
    m_proximityThreshold = proximityThreshold;

    m_moving = false;
    m_velocity = 0.0f;

    m_direction = KBVectorValue(0.0f);
    m_destination = 0;

    m_sensorGPS = new KBSensorGPSDummy();
}

KBBusDummy::~KBBusDummy(void)
{
    delete m_sensorGPS;
}

void KBBusDummy::init(void)
{
    int source = getRandomTransit();

    KBVector pos = m_transits[source]->getPosition();
    m_sensorGPS->setLongitude(pos.x);
    m_sensorGPS->setLatitude(pos.y);

    m_destination = getRandomTransit();
}

void KBBusDummy::update(void)
{
    m_sensorGPS->update();

    if (m_moving) {
        KBVector dst = m_transits[m_destination]->getPosition();
        KBVector cur = KBVectorCreate(m_sensorGPS->getLongitude(), m_sensorGPS->getLatitude());

        if (KBVectorMagnitude(KBVectorSubtract(dst, cur)) <= m_proximityThreshold) {
            m_destination = getRandomTransit();
            return;
        }

        KBVector dir = KBVectorNormalize(KBVectorSubtract(dst, cur));
        KBVector vel = KBVectorMultiply(KBVectorValue(m_velocity), dir);

        KBVector next = KBVectorAdd(cur, vel);
        m_sensorGPS->setLongitude(next.x);
        m_sensorGPS->setLatitude(next.y);

        m_direction = dir;
    }
}

KBVector KBBusDummy::getPosition(void)
{
    KBVector pos;
    pos.x = m_sensorGPS->getLongitude();
    pos.y = m_sensorGPS->getLatitude();
    return pos;
}

KBVector KBBusDummy::getDirection(void)
{
    return m_direction;
}

bool KBBusDummy::isMoving(void)
{
    return m_moving;
}

void KBBusDummy::setMoving(bool value)
{
    m_moving = value;
}

float KBBusDummy::getVelocity(void)
{
    return m_velocity;
}

void KBBusDummy::setVelocity(float value)
{
    m_velocity = value;
}

int KBBusDummy::getRandomTransit(void)
{
    return (int)(KBRandom() * (float)m_transits.size());
}
