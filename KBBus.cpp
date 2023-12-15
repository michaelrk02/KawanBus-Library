#include "Arduino.h"
#include "KBSensorGPS.h"
#include "KBSensorAccel.h"
#include "KBServer.h"
#include "KBTransit.h"

#include "KBBus.h"

KBBusDummy::KBBusDummy(KBServer *server, KBUID id, float proximityThreshold)
{
    m_server = server;
    m_id = id;
    m_proximityThreshold = proximityThreshold;

    m_moving = false;
    m_timer = 0;

    m_sensorGPS = new KBSensorGPSDummy();
    m_sensorAccel = new KBSensorAccelProto(KB_PROTO_ACCEL_PIN, 0.3f);
    m_direction = KBVectorValue(0.0f);
    m_destination = 0;
}

KBBusDummy::~KBBusDummy(void)
{
    delete m_sensorAccel;
    delete m_sensorGPS;
}

void KBBusDummy::init(void)
{
    m_sensorGPS->init();
    m_sensorAccel->init();

    int source = getRandomTransit();

    std::vector<KBTransit *> transits = m_server->getTransits();
    KBVector pos = transits[source]->getPosition();
    m_sensorGPS->setLongitude(pos.x);
    m_sensorGPS->setLatitude(pos.y);

    m_destination = getRandomTransit();
}

void KBBusDummy::update(void)
{
    unsigned long now = millis();

    m_sensorGPS->update();
    m_sensorAccel->update();

    if (m_moving) {
        if (now - m_timer > 1000) {
            std::vector<KBTransit *> transits = m_server->getTransits();

            KBVector dst = KBCoordinateGeographicToSpatial(transits[m_destination]->getPosition());
            KBVector cur = KBCoordinateGeographicToSpatial(KBVectorCreate(m_sensorGPS->getLongitude(), m_sensorGPS->getLatitude()));

            if (KBVectorMagnitude(KBVectorSubtract(dst, cur)) <= m_proximityThreshold) {
                m_destination = getRandomTransit();
                return;
            }

            KBVector dir = KBVectorNormalize(KBVectorSubtract(dst, cur));
            KBVector vel = KBVectorMultiply(KBVectorValue(getVelocity() / 3600.0f), dir);

            KBVector next = KBCoordinateSpatialToGeographic(KBVectorAdd(cur, vel));
            m_sensorGPS->setLongitude(next.x);
            m_sensorGPS->setLatitude(next.y);

            m_direction = dir;

            m_timer = now;
        }
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
    if (m_id != m_server->getTrackID()) {
        return 0.0f;
    }

    return m_sensorAccel->getVelocity();
}

int KBBusDummy::getRandomTransit(void)
{
    return (int)(KBRandom() * (float)m_server->getTransits().size());
}
