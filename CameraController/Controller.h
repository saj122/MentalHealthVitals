#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <memory>

namespace MHV
{
    class OpenNICamera;
}

namespace MHV
{
    class Controller
    {
        public:
            Controller();
            ~Controller();
            void start();
        private:
            std::unique_ptr<MHV::OpenNICamera> _openNICamera;
    };
}

#endif // CONTROLLER_H
