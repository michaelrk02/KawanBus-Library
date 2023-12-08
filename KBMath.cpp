#include <math.h>
#include <stdlib.h>

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
    return sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f));
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

