#define GOOGLE_STRIP_LOG 1
#include <glog/logging.h>

#include <tensorflow/c/c_api.h>

#include <opencv2/opencv.hpp>

int main(int argc, char *argv[]) {
    google::InitGoogleLogging(argv[0]);

#ifndef NDEBUG
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 0;
#endif

    TF_Session *sess;
    TF_Graph *graph;

    TF_Status* status = TF_NewStatus();
    TF_SessionOptions* options = TF_NewSessionOptions();
    uint8_t config[11] = {0x32, 0x09, 0x09, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xe3, 0x3f};
    TF_SetConfig(options, (void*)config, 11, status);

    TF_Status* s = TF_NewStatus();

    TF_CloseSession(sess,s);
    TF_DeleteSession(sess,s);
    TF_DeleteGraph(graph);
    TF_DeleteStatus(s);

    cv::destroyAllWindows();
    return 0;
}

