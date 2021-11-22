# MentalHealthVitals

### Build from source:
OS - Mac OS X

Install dependencies:
1. Install homebrew and xcode.
2. Run in terminal
   
       xcode-select --install
       brew install ossp-uuid cmake rapidjson glog gflags googletest qt gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly opencv pkg-config sqlite3

3. Build & Install OpenSSL

       wget --no-check-certificate https://www.openssl.org/source/openssl-3.0.0.tar.gz
       tar xf openssl-3.0.0.tar.gz
       cd openssl-3.0.0
       ./Configure
       make 
       sudo make install

4. Download tensorflow gpu if you have an nvidia gpu with drivers and CUDA installed otherwise download cpu version.
   https://www.tensorflow.org/install/lang_c
5. Extract to /usr/local

       sudo tar xf <FILE>.tar.gz -C /usr/local

Build:

    mkdir build 
    cd build
    cmake -G Xcode -DCMAKE_FIND_FRAMEWORK=LAST .. 
    Open project in xcode and BUILD_ALL.


OS - Ubuntu 21.04

Install dependencies:
1. Run in terminal
       
       sudo apt update && sudo apt install -y libssl-dev libsqlite3-dev rapidjson-dev build-essential libgl1-mesa-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 libgflags-dev libgoogle-glog-dev libgmock-dev libgtest-dev libopencv-dev curl cmake git wget

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

### Unit Tests:
### Verification Test:
