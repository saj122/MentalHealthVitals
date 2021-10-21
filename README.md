# MentalHealthVitals

### Build from source:
OS - Mac OS X

Install dependencies:
1. Install homebrew.
2. brew install cmake rapidjson glog gflags googletest libtensorflow qt gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly opencv pkg-config

Build:

    mkdir build 
    cd build
    cmake -G Xcode ..
    Open project in xcode and BUILD_ALL.


OS - Ubuntu 21.04

Install dependencies:
1. sudo apt install -y libgflags-dev libgoogle-glog-dev libgmock-dev libgtest-dev libopencv-dev curl cmake git
2. Download tensorflow gpu if you have an nvidia gpu with drivers and CUDA installed otherwise download cpu version.
   https://www.tensorflow.org/install/lang_c
3. Extract to /usr/local - sudo tar -C /usr/local -xzf <FILE>.tar.gz && sudo ldconfig
4. Run as sudo and install Qt6 6.1.3 https://www.qt.io/download >> Go open source

Build:

    mkdir build 
    cd build
    cmake -DCMAKE_PREFIX_PATH=/opt/Qt/6.1.3/gcc_64/lib/cmake ..
    make -j$(nproc)
