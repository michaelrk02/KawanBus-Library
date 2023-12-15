#ifndef KAWANBUS_MATH_H
#define KAWANBUS_MATH_H

struct KBVector
{
    float x;
    float y;
};

KBVector KBVectorValue(float s);
KBVector KBVectorCreate(float x, float y);

KBVector KBVectorNegate(KBVector v);
KBVector KBVectorInvert(KBVector v);
float KBVectorMagnitude(KBVector v);
KBVector KBVectorNormalize(KBVector v);

KBVector KBVectorAdd(KBVector v1, KBVector v2);
KBVector KBVectorSubtract(KBVector v1, KBVector v2);
KBVector KBVectorMultiply(KBVector v1, KBVector v2);
KBVector KBVectorDivide(KBVector v1, KBVector v2);
float KBVectorDotProduct(KBVector v1, KBVector v2);

float KBRandom(void);

KBVector KBCoordinateGeographicToSpatial(KBVector v);
KBVector KBCoordinateSpatialToGeographic(KBVector v);

#endif
