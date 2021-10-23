#define GOOGLE_STRIP_LOG 1
#include <glog/logging.h>

#include <tensorflow/c/c_api.h>

#include <opencv2/opencv.hpp>

#include "MemoryFactory.h"

int main(int argc, char *argv[])
{
    google::InitGoogleLogging(argv[0]);

#ifndef NDEBUG
    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 0;
#endif
    std::unique_ptr<MHV::Memory> mem = MHV::MemoryFactory::create(640*480*3, 640*480*2, 640*480*3);

    cv::CascadeClassifier clfr(HAARCASCADE_PATH);

    std::vector<cv::Rect> features;

    while(1)
    {
        const unsigned char *data = mem->getRGBData();
        cv::Mat image = cv::Mat(480, 640, CV_8UC3, (void *) data);
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);

        cv::Mat grayscale_image;
        cv::cvtColor(image, grayscale_image, cv::COLOR_RGB2GRAY);
        cv::equalizeHist(grayscale_image, grayscale_image);

        clfr.detectMultiScale(grayscale_image, features, 1.05, 12, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

        for (auto &feature: features)
            cv::rectangle(image, feature, cv::Scalar(0, 255, 0), 2);

        cv::imshow("Image", image);
        LOG(INFO) << features.size();

        switch (cv::waitKey(10)) {
            case 'q':
                std::exit(EXIT_SUCCESS);
            case 'Q':
                std::exit(EXIT_SUCCESS);
            default:
                break;
        }
    }
    return 0;
}

