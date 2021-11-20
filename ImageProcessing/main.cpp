#define GOOGLE_STRIP_LOG 1
#include <glog/logging.h>

#include <tensorflow/c/c_api.h>

#include <opencv2/opencv.hpp>

#include "MemoryFactory.h"

#include <csignal>

volatile bool __stop;

void sigHandler(int s)
{
    __stop = true;
}

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

#ifndef NDEBUG
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 0;
#endif
    __stop = false;
    std::signal(SIGINT,  sigHandler);
    std::signal(SIGTERM, sigHandler);

    std::unique_ptr<MHV::Memory> mem = MHV::MemoryFactory::create(640*480*3, 640*480*2, 640*480*3);

    cv::CascadeClassifier clfr(HAARCASCADE_PATH);

    std::vector<cv::Rect> features;
    float* box = new float[4];

    while(!__stop)
    {
        const unsigned char *data = mem->getRGBData();
        cv::Mat image = cv::Mat(480, 640, CV_8UC3, (void *) data);
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

        cv::Mat grayscale_image;
        cv::cvtColor(image, grayscale_image, cv::COLOR_RGB2GRAY);
        cv::equalizeHist(grayscale_image, grayscale_image);

        clfr.detectMultiScale(grayscale_image, features, 1.05, 12, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(32, 32));

        if(!features.empty())
        {
            box[0] = features[0].x;
            box[1] = features[0].y;
            box[2] = features[0].width;
            box[3] = features[0].height;

            mem->setDetectionBox(box);
        }
    }
    delete[] box;
    return 0;
}

