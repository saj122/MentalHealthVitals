# MentalHealthVitals

###Build from source:
OS - Ubuntu 21.04

Install dependencies:
1. sudo apt install -y libgflags-dev libgoogle-glog-dev libgmock-dev libgtest-dev libopencv-dev curl cmake
2. Download tensorflow gpu if you have an nvidia gpu with drivers and CUDA installed otherwise download cpu version.
   https://www.tensorflow.org/install/lang_c
3. Extract to /usr/local
4. Install Qt6 6.1.3 https://www.qt.io/download >> Go open source
5. Install OpenNI SDK and driver for linux.
   https://orbbec3d.com/develop/

Build:

    mkdir build 
    cd build
    cmake -DCMAKE_PREFIX_PATH=/opt/Qt/6.1.3/gcc_64/lib/cmake ..
    make -j$(nproc)
