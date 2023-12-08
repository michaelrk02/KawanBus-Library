#include "KBMath.h"

#include "KBSensorGPS.h"

KBSensorGPSDummy::KBSensorGPSDummy(const std::vector<KBVector> &nodes, float nodeThreshold)
{
    m_nodes = nodes;
    m_nodeThreshold = nodeThreshold;

    m_moving = false;
    m_velocity = 0.0f;

    m_destination = 0;
    m_longitude = 0.0f;
    m_latitude = 0.0f;
}

KBSensorGPSDummy::~KBSensorGPSDummy(void)
{
}

void KBSensorGPSDummy::init(void)
{
    int source = getRandomNode();
    m_latitude = m_nodes[source].x;
    m_longitude = m_nodes[source].y;

    m_destination = getRandomNode();
}

void KBSensorGPSDummy::update(void)
{
    if (m_moving) {
        KBVector dst = m_nodes[m_destination];
        KBVector cur = KBVectorCreate(m_longitude, m_latitude);

        if (KBVectorMagnitude(KBVectorSubtract(dst, cur)) <= m_nodeThreshold) {
            m_destination = getRandomNode();
            return;
        }

        KBVector dir = KBVectorNormalize(KBVectorSubtract(dst, cur));
        KBVector vel = KBVectorMultiply(KBVectorValue(m_velocity), dir);

        KBVector next = KBVectorAdd(cur, vel);
        m_longitude = next.x;
        m_latitude = next.y;
    }
}

float KBSensorGPSDummy::getLongitude(void)
{
    return m_longitude;
}

float KBSensorGPSDummy::getLatitude(void)
{
    return m_latitude;
}

bool KBSensorGPSDummy::isMoving(void)
{
    return m_moving;
}

void KBSensorGPSDummy::setMoving(bool value)
{
    m_moving = value;
}

float KBSensorGPSDummy::getVelocity(void)
{
    return m_velocity;
}

void KBSensorGPSDummy::setVelocity(float value)
{
    m_velocity = value;
}

int KBSensorGPSDummy::getRandomNode(void)
{
    return (int)(KBRandom() * (float)m_nodes.size());
}
