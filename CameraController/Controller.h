#ifndef CONTROLLER_H
#define CONTROLLER_H

class Astra;

class Controller
{
    public:
        Controller();
        ~Controller();
        void start();
    private:
        Astra* _astra;
};

#endif // CONTROLLER_H
