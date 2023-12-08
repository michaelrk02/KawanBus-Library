#ifndef KAWANBUS_SERVER_H
#define KAWANBUS_SERVER_H

class KBTransit;
class KBBus;

class KBServer
{
public:
    virtual std::vector<KBTransit *> getTransits(void) = 0;
    virtual std::vector<KBBus *> getBuses(void) = 0;
};

#endif
