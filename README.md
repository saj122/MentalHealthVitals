# MentalHealthVitals

### Build from source:
OS - Mac OS X

Install dependencies:
1. Install homebrew and xcode.
2. Run in terminal
   
       xcode-select --install
       brew install mongo-c-driver cmake rapidjson glog gflags googletest libtensorflow qt gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly opencv pkg-config
       brew tap mongodb/brew
       brew install mongodb-community@5.0
       brew services start mongodb-community@5.0
3. Build mongodb C++ driver
       
       curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.6/mongo-cxx-driver-r3.6.6.tar.gz
       tar -xzf mongo-cxx-driver-r3.6.6.tar.gz
       cd mongo-cxx-driver-r3.6.6/build
       cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/usr/local/opt/mongo-c-driver/lib/cmake -DCMAKE_INSTALL_PREFIX=/usr/local
       sudo cmake --build . --target EP_mnmlstc_core
       cmake --build .
       sudo cmake --build . --target install
4. Install Open3D
 
       git clone --recursive https://github.com/intel-isl/Open3D.git
       cd Open3D
       mkdir build
       cd build
       cmake -DBUILD_SHARED_LIBS=ON -DBUILD_GUI=OFF -DBUILD_WEBRTC=OFF DCMAKE_INSTALL_PREFIX=/usr/local ..
       make -j$(sysctl -n hw.physicalcpu)
       sudo make install

Build:

    mkdir build 
    cd build
    cmake -G Xcode ..
    Open project in xcode and BUILD_ALL.


OS - Ubuntu 21.04

Install dependencies:
1. Run in terminal
       
       sudo apt update && sudo apt install -y rapidjson-dev build-essential libgl1-mesa-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev libgstreamer-plugins-bad1.0-dev gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio++-dev libc++abi-dev libbson-dev libgflags-dev libgoogle-glog-dev libgmock-dev libgtest-dev libopencv-dev curl cmake git wget
2. Download tensorflow gpu if you have an nvidia gpu with drivers and CUDA installed otherwise download cpu version.
   https://www.tensorflow.org/install/lang_c
3. Extract to /usr/local 

       sudo tar -C /usr/local -xzf <FILE>.tar.gz && sudo ldconfig
4. Run as sudo and install Qt6 6.1.3 https://www.qt.io/download >> Go open source or install aqtinstall and install from the cli
5. Install mongodb

       wget -qO - https://www.mongodb.org/static/pgp/server-5.0.asc | sudo apt-key add -
       echo "deb [ arch=amd64,arm64 ] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/5.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-5.0.list
       sudo apt update
       sudo apt-get install -y mongodb-org
       sudo systemctl start mongod
       sudo systemctl daemon-reload
6. Build mongodb C driver
   
       wget https://github.com/mongodb/mongo-c-driver/releases/download/1.19.1/mongo-c-driver-1.19.1.tar.gz
       tar xzf mongo-c-driver-1.19.1.tar.gz
       cd mongo-c-driver-1.19.1
       mkdir cmake-build
       cd cmake-build
       cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
       cmake --build .
       sudo cmake --build . --target install
7. Build mongodb C++ driver

       curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.6/mongo-cxx-driver-r3.6.6.tar.gz
       tar -xzf mongo-cxx-driver-r3.6.6.tar.gz
       cd mongo-cxx-driver-r3.6.6/build
       cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local
       sudo cmake --build . --target EP_mnmlstc_core
       cmake --build .
       sudo cmake --build . --target install
8. Install Open3D
       
       git clone --recursive https://github.com/intel-isl/Open3D.git
       cd Open3D
       cd util
       ./install_deps_ubuntu.sh
       cd ..
       mkdir build
       cd build
       cmake -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=/usr/local .. 
       Note: Use -DBUILD_CUDA_MODULE=ON if using an Nvidia GPU
       make -j$(nproc)
       sudo make install

Build:

    mkdir build 
    cd build
    cmake -DCMAKE_PREFIX_PATH=/opt/Qt/6.1.3/gcc_64/lib/cmake ..
    make -j$(nproc)
