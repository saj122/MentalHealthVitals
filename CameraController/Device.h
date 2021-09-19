#ifndef DEVICE_H
#define DEVICE_H


class Device
{
    public:
        virtual void init() = 0;
        virtual void run() = 0;
};

#endif // DEVICE_H
