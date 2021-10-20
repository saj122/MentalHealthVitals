#include "GSCamera.h"

#include "MemoryFactory.h"

#include <gst/app/app.h>

#include <glog/logging.h>

MHV::GSCamera::GSCamera(int width, int height) : _pipeline(nullptr),
                                                 _buffer(nullptr),
                                                 _sample(nullptr),
                                                 _sink(nullptr),
                                                 _width(width),
                                                 _height(height)
{
    _utils = MemoryFactory::create(width*height*3);
}

MHV::GSCamera::~GSCamera()
{
    gst_sample_unref (_sample);
    gst_element_set_state(_pipeline, GST_STATE_NULL);
    gst_object_unref(_pipeline);
}

void MHV::GSCamera::init()
{
    LOG(INFO) << "Init GST.";
    gst_init(NULL, NULL);

    LOG(INFO) << "Creating pipeline.";
    _pipeline = gst_parse_launch(
                "v4l2src device=/dev/video0 ! videoconvert ! video/x-raw, width=640, height=480, format=RGB ! appsink name=sink",
                nullptr);

    gst_element_set_state (_pipeline, GST_STATE_PLAYING);

    _sink = gst_bin_get_by_name(GST_BIN(_pipeline), "sink");
    if (_sink == NULL)
    {
        LOG(ERROR) << "Failed to get sink.";
        return;
    }
}

void MHV::GSCamera::run()
{
    if(isValid())
    {
        _sample = gst_app_sink_pull_sample(GST_APP_SINK(_sink));
        if (_sample == NULL)
        {
            LOG(ERROR) << "Failed to get sample.";
            return;
        }

        _buffer = gst_sample_get_buffer(_sample);
        GstMapInfo map;

        gst_buffer_map(_buffer, &map, GST_MAP_READ);

        _utils->setRGBData(map.data);

        gst_buffer_unmap (_buffer, &map);
    }
}

bool MHV::GSCamera::isValid()
{
    return true;
}
