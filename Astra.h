#ifndef ASTRA_H
#define ASTRA_H

#include "Device.h"

#include <OpenNI.h>

#include <QObject>

#define MAX_DEPTH 10000

class Astra : public QObject, public Device
{
    Q_OBJECT

    public:
        enum class DisplayModes
        {
            DISPLAY_MODE_OVERLAY,
            DISPLAY_MODE_DEPTH,
            DISPLAY_MODE_IMAGE
        };
    public:
        Astra();
        ~Astra();
        void init() override;
        openni::Device& getDevice() override
        {
            return _device;
        }

        openni::VideoStream& getColorStream() override
        {
            return _color;
        }

        openni::VideoStream& getDepthStream() override
        {
            return _depth;
        }
    public slots:
        void process();
    signals:
        void finished();
        void error(QString err);
    private:
        openni::Device _device;
        openni::VideoStream _depth;
        openni::VideoStream _color;
        openni::VideoStream** _streams;
        openni::VideoMode _depthVideoMode;
        openni::VideoMode _colorVideoMode;
        openni::VideoFrameRef _colorFrame;
        openni::VideoFrameRef _depthFrame;

        int _width;
        int _height;
};

#endif // ASTRA_H
