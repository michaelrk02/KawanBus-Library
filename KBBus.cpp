#include "KBSensorGPS.h"
#include "KBServer.h"
#include "KBTransit.h"

#include "KBBus.h"

KBBusDummy::KBBusDummy(KBServer *server, KBUID id, float proximityThreshold)
{
    m_server = server;
    m_id = id;
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

    std::vector<KBTransit *> transits = m_server->getTransits();
    KBVector pos = transits[source]->getPosition();
    m_sensorGPS->setLongitude(pos.x);
    m_sensorGPS->setLatitude(pos.y);

    m_destination = getRandomTransit();
}

void KBBusDummy::update(void)
{
    m_sensorGPS->update();

    if (m_moving) {
        std::vector<KBTransit *> transits = m_server->getTransits();

        KBVector dst = transits[m_destination]->getPosition();
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

KBUID KBBusDummy::getID(void)
{
    return m_id;
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
    return (int)(KBRandom() * (float)m_server->getTransits().size());
}
