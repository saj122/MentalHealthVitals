#ifndef CONTROLLER_H
#define CONTROLLER_H

class OpenNICamera;

class Controller
{
    public:
        Controller();
        ~Controller();
        void start();
    private:
        OpenNICamera* _openNICamera;
};

#endif // CONTROLLER_H
