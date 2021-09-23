#include <iostream>

#include "Controller.h"

int main(int argc, char *argv[])
{
    MHV::Controller ct;
    try
    {
        ct.start();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
