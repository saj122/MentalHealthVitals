# MentalHealthVitals

[![CI](https://github.com/saj122/MentalHealthVitals/blob/main/.github/workflows/mac-cmake/badge.svg)](https://github.com/saj122/MentalHealthVitals/blob/main/.github/workflows/mac-cmake.yml)

### Build from source:
OS - Mac OS X

Install dependencies:
1. Install homebrew and xcode.
2. Run in terminal
   
       xcode-select --install
       brew install openssl ossp-uuid cmake rapidjson glog gflags googletest qt gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly opencv pkg-config sqlite3
       brew link openssl --force

3. Download tensorflow gpu if you have an nvidia gpu with drivers and CUDA installed otherwise download cpu version.
   https://www.tensorflow.org/install/lang_c

   Note: If system is arm64, tensorflow cc api needs to be built and copied to /usr/local instead. Downloadable libraries were built with amd64.   

4. Extract to /usr/local

       sudo tar xf <FILE>.tar.gz -C /usr/local

Build:

    mkdir build 
    cd build
    cmake -G Xcode -DCMAKE_FIND_FRAMEWORK=LAST -DOPENSSL_INCLUDE_DIR=/usr/local/include .. 
    
Open project in xcode and BUILD_ALL.

OS - ![Ubuntu](https://img.shields.io/badge/Ubuntu-E95420?style=for-the-badge&logo=ubuntu&logoColor=white)

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
Tests are implemented with CTest and GTest:

    cd build
    make test

### Verification Test:
OS - Mac OS X

1. Install Dotnet 3

       brew tap isen-ng/dotnet-sdk-versions  
       brew install --cask dotnet-sdk3-1-400

2. Install P and Coyote

       brew install java
       dotnet tool install --global P
       dotnet tool install --global Microsoft.Coyote.CLI --version 1.0.5

3. Build P Project

       cd VerificationTest
       pc -proj:VerificationTest.pproj

4. Run Tests

       cd VerificationTest/POutput/netcoreapp3.1
       coyote test VerificationTest.dll -m PImplementation.tcRW.Execute -i 1000

OS - Ubuntu 21.04

1. Install Dotnet 3

       wget https://packages.microsoft.com/config/ubuntu/21.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
       sudo dpkg -i packages-microsoft-prod.deb
       rm packages-microsoft-prod.deb
       sudo apt-get update
       sudo apt-get install -y apt-transport-https
       sudo apt-get update
       sudo apt-get install -y dotnet-sdk-3.1


3. Install P and Coyote

       sudo apt-get install default-jre
       dotnet tool install --global P
       dotnet tool install --global Microsoft.Coyote.CLI --version 1.0.5

4. Build P Project

       cd VerificationTest
       pc -proj:VerificationTest.pproj

5. Run Tests

       cd VerificationTest/POutput/netcoreapp3.1
       coyote test VerificationTest.dll -m PImplementation.tcRW.Execute -i 1000


