# MentalHealthVitals

### Build from source:
OS - Mac OS X

Install dependencies:
1. Install homebrew and xcode.
2. Run in terminal
   
       xcode-select --install
       brew install openssl mongo-c-driver cmake rapidjson glog gflags googletest libtensorflow qt gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly opencv pkg-config sqlite3

Build:

    mkdir build 
    cd build
    cmake -G Xcode ..
    Open project in xcode and BUILD_ALL.


OS - Ubuntu 21.04

Install dependencies:
1. Run in terminal
       
       sudo apt update && sudo apt install -y libssl-dev libsqlite3-dev rapidjson-dev build-essential libgl1-mesa-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio++-dev libc++abi-dev libbson-dev libgflags-dev libgoogle-glog-dev libgmock-dev libgtest-dev libopencv-dev curl cmake git wget

2. Download tensorflow gpu if you have an nvidia gpu with drivers and CUDA installed otherwise download cpu version.
   https://www.tensorflow.org/install/lang_c
3. Extract to /usr/local 

       sudo tar -C /usr/local -xzf <FILE>.tar.gz && sudo ldconfig
4. Run as sudo and install Qt6 6.1.3 https://www.qt.io/download >> Go open source or install aqtinstall and install from the cli

Build:

    mkdir build 
    cd build
    cmake -DCMAKE_PREFIX_PATH=/opt/Qt/6.1.3/gcc_64/lib/cmake ..
    make -j$(nproc)
