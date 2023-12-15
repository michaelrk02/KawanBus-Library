#include "Arduino.h"

#include "KBSensorAccel.h"

KBSensorAccelProto::KBSensorAccelProto(int pin, float wheelRadius)
{
    m_pin = pin;
    m_wheelRadius = wheelRadius;
}

void KBSensorAccelProto::init(void)
{
    m_lastCycle = 0;
    m_velocity = 0.0f;
}

void KBSensorAccelProto::update(void)
{
    int state = digitalRead(m_pin);
    if (state != m_state) {
        if (state == LOW) {
            unsigned long now = millis();

            float period = (float)(now - m_lastCycle) / 1000.0f;
            float frequency = 1.0f / period;
            m_velocity = 2.0f * PI * m_wheelRadius * frequency * 3600.0f / 1000.0f;

            m_lastCycle = now;
        }

        m_state = state;
    } else {
        float interval = (float)(millis() - m_lastCycle) / 1000.0f;
        if (interval > 1.0f) {
            m_velocity = 0.0f;
        }
    }
}

float KBSensorAccelProto::getVelocity(void)
{
    return m_velocity;
}
