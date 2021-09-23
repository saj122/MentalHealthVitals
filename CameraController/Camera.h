#ifndef CAMERA_H
#define CAMERA_H

namespace MHV
{
    class Camera
    {
        public:
            virtual void init() = 0;
            virtual void run() = 0;
            virtual bool isValid() = 0;
    };
};

#endif // CAMERA_H
