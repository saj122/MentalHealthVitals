#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

#include "Camera.h"

namespace MHV
{
    class Controller
    {
        public:
            Controller();
            ~Controller();
            void start();
        private:
            std::unique_ptr<MHV::Camera> _camera;
            const char* _settings;
    };
}

#endif // CONTROLLER_H
