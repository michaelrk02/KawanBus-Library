#include <stdlib.h>

#include "Arduino.h"

#include "KBMath.h"

KBVector KBVectorValue(float s)
{
    KBVector v;
    v.x = s;
    v.y = s;
    return v;
}

KBVector KBVectorCreate(float x, float y)
{
    KBVector v;
    v.x = x;
    v.y = y;
    return v;
}

KBVector KBVectorNegate(KBVector v)
{
    KBVector u;
    u.x = -v.x;
    u.y = -v.y;
    return u;
}

KBVector KBVectorInvert(KBVector v)
{
    KBVector u;
    u.x = 1.0f / v.x;
    u.y = 1.0f / v.y;
    return u;
}

float KBVectorMagnitude(KBVector v)
{
    return sqrt(pow(v.x, 2.0f) + pow(v.y, 2.0f));
}

KBVector KBVectorNormalize(KBVector v)
{
    float mag = KBVectorMagnitude(v);
    KBVector u;
    u.x = v.x / mag;
    u.y = v.y / mag;
    return u;
}

KBVector KBVectorAdd(KBVector v1, KBVector v2)
{
    KBVector u;
    u.x = v1.x + v2.x;
    u.y = v1.y + v2.y;
    return u;
}

KBVector KBVectorSubtract(KBVector v1, KBVector v2)
{
    KBVector u;
    u.x = v1.x - v2.x;
    u.y = v1.y - v2.y;
    return u;
}

KBVector KBVectorMultiply(KBVector v1, KBVector v2)
{
    KBVector u;
    u.x = v1.x * v2.x;
    u.y = v1.y * v2.y;
    return u;
}

KBVector KBVectorDivide(KBVector v1, KBVector v2)
{
    KBVector u;
    u.x = v1.x / v2.x;
    u.y = v1.y / v2.y;
    return u;
}

float KBVectorDotProduct(KBVector v1, KBVector v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

float KBRandom(void)
{
    float x = (float)std::rand();
    float max = (float)RAND_MAX;
    return x / max;
}

KBVector KBCoordinateGeographicToSpatial(KBVector v)
{
    KBVector u;
    u.x = v.x * 111.320f * cos(v.y / 180.0f * PI);
    u.y = v.y * 110.574f;
    return u;
}

KBVector KBCoordinateSpatialToGeographic(KBVector v)
{
    KBVector u;
    u.y = v.y / 110.574f;
    u.x = v.x / (111.320f * cos(u.y / 180.0f * PI));
    return u;
}

