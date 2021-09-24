#include "Controller.h"

#define GOOGLE_STRIP_LOG 1
#include <glog/logging.h>

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

#ifndef NDEBUG
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 0;
#endif

    MHV::Controller ct;
    ct.start();

    return 0;
}
