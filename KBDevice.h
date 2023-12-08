#ifndef KAWANBUS_DEVICE_H
#define KAWANBUS_DEVICE_H

class KBDevice
{
public:
    virtual void init(void) = 0;
    virtual void update(void) = 0;
};

#endif
