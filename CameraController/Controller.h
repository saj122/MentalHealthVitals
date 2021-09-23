#ifndef CONTROLLER_H
#define CONTROLLER_H

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
            MHV::OpenNICamera* _openNICamera;
    };
}

#endif // CONTROLLER_H
