#include <map>

#include "Arduino.h"
#include "KBSensorGPS.h"
#include "KBServer.h"
#include "KBBus.h"

#include "KBTransit.h"

KBTransitDummy::KBTransitDummy(KBServer *server, KBUID id, float rangeThreshold, float proximityThreshold)
{
    m_server = server;
    m_id = id;
    m_rangeThreshold = rangeThreshold;
    m_proximityThreshold = proximityThreshold;

    m_sensorGPS = new KBSensorGPSDummy();
}

KBTransitDummy::~KBTransitDummy(void)
{
    delete m_sensorGPS;
}

void KBTransitDummy::init(void)
{
    m_sensorGPS->init();

    m_nearestBus = 0;
    m_nearestDistance = 0;
    m_nearestTime = 0;
}

void KBTransitDummy::update(void)
{
    m_sensorGPS->update();

    std::vector<KBBus *> buses = m_server->getBuses();

    std::map<KBUID, KBBus *> busIndex;
    for (int i = 0; i < buses.size(); i++) {
        busIndex[buses[i]->getID()] = buses[i];
    }

    KBUID nearest = 1;
    float nearestDistance = 0.0f;
    float nearestVelocity = 0.0f;
    for (int i = 0; i < buses.size(); i++) {
        KBVector transitPos = KBCoordinateGeographicToSpatial(getPosition());
        KBVector busPos = KBCoordinateGeographicToSpatial(buses[i]->getPosition());

        float distance = KBVectorMagnitude(KBVectorSubtract(busPos, transitPos));
        if ((distance <= m_rangeThreshold) && (m_inRange.count(buses[i]->getID()) == 0)) {
            m_inRange.insert(buses[i]->getID());

            Serial.print("Bus ");
            Serial.print(buses[i]->getID());
            Serial.print(" is entering transit ");
            Serial.print(m_id);
            Serial.println("");

            if (buses[i]->getID() == m_server->getTrackID()) {
                m_server->sendTransitInRange(m_id);
            }
        }
        if ((distance <= m_proximityThreshold) && (m_inProximity.count(buses[i]->getID()) == 0)) {
            m_inProximity.insert(buses[i]->getID());

            Serial.print("Bus ");
            Serial.print(buses[i]->getID());
            Serial.print(" is stopping at transit ");
            Serial.print(m_id);
            Serial.println("");

            if (buses[i]->getID() == m_server->getTrackID()) {
                m_server->sendTransitInProximity(m_id);
            }
        }

        KBVector nearestBusPos = KBCoordinateGeographicToSpatial(busIndex[nearest]->getPosition());
        if (abs(KBVectorMagnitude(KBVectorSubtract(nearestBusPos, transitPos)) - distance) < 0.05) {
            nearest = buses[i]->getID();
            nearestDistance = distance;
            nearestVelocity = buses[i]->getVelocity();
        }
    }

    m_nearestBus = nearest;
    m_nearestDistance = (int)(nearestDistance * 1000.0f);
    m_nearestTime = (int)((nearestDistance + 1.0f) / (nearestVelocity + 1.0f) * 3600.0f);

    for (std::set<KBUID>::iterator it = m_inProximity.begin(); it != m_inProximity.end(); ) {
        KBUID id = *it;
        KBVector transitPos = KBCoordinateGeographicToSpatial(getPosition());
        KBVector busPos = KBCoordinateGeographicToSpatial(busIndex[id]->getPosition());

        float distance = KBVectorMagnitude(KBVectorSubtract(busPos, transitPos));
        if (distance > m_proximityThreshold) {
            it = m_inProximity.erase(it);

            Serial.print("Bus ");
            Serial.print(id);
            Serial.print(" is leaving transit ");
            Serial.print(m_id);
            Serial.println("");

            if (id == m_server->getTrackID()) {
                m_server->sendTransitInProximity(0);
            }
        } else {
            ++it;
        }
    }

    for (std::set<KBUID>::iterator it = m_inRange.begin(); it != m_inRange.end(); ) {
        KBUID id = *it;
        KBVector transitPos = KBCoordinateGeographicToSpatial(getPosition());
        KBVector busPos = KBCoordinateGeographicToSpatial(busIndex[id]->getPosition());

        float distance = KBVectorMagnitude(KBVectorSubtract(busPos, transitPos));
        if (distance > m_rangeThreshold) {
            it = m_inRange.erase(it);

            Serial.print("Bus ");
            Serial.print(id);
            Serial.print(" is out of transit ");
            Serial.print(m_id);
            Serial.print(" range");
            Serial.println("");

            if (id == m_server->getTrackID()) {
                m_server->sendTransitInRange(0);
            }
        } else {
            ++it;
        }
    }
}

KBUID KBTransitDummy::getID(void)
{
    return m_id;
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

KBUID KBTransitDummy::getNearestBusID(void)
{
    return m_nearestBus;
}

int KBTransitDummy::getNearestBusDistance(void)
{
    return m_nearestDistance;
}

int KBTransitDummy::getNearestBusETA(void)
{
    return m_nearestTime;
}
