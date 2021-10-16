FROM ubuntu:21.04

COPY . /MentalHealthVitals

ENV QT_X11_NO_MITSHM 1
ENV QT_QPA_PLATFORM_PLUGIN_PATH /6.2.0/gcc_64/plugins
ENV QT_PLUGIN_PATH /6.2.0/gcc_64/plugins
ENV XPRA_SCALING 0

RUN apt-get update && DEBIAN_FRONTEND="noninteractive" TZ="America/Chicago" apt-get -y install tzdata

VOLUME /tmp/.X11-unix
ENV DISPLAY :80

RUN apt update \
    && DEBIAN_FRONTEND=noninteractive apt install -y wget gnupg xvfb x11-xserver-utils python3-pip \
    && pip3 install pyinotify \
    && DEBIAN_FRONTEND=noninteractive apt install -y xpra \
    && mkdir -p /run/user/0/xpra

RUN DEBIAN_FRONTEND="noninteractive" apt-get install -y build-essential  \
                   libgl1-mesa-dev  \
                   python3-pip  \
                   p7zip-full  \
                   libgflags-dev  \
                   libgoogle-glog-dev \
                   libgmock-dev  \
                   libgtest-dev  \
                   libopencv-dev  \
                   curl  \
                   cmake  \
				   make \
                   wget \
                   xcb \
                   libxkbcommon-x11-dev \
                   libxcb-xinerama0 \
                   libxcb-xinerama0-dev \
				   libusb-dev \
				   usbutils \
				   libglapi-mesa \
                   dbus-x11

RUN wget -qO - https://packages.lunarg.com/lunarg-signing-key-pub.asc | apt-key add -
RUN wget -qO /etc/apt/sources.list.d/lunarg-vulkan-1.2.189-focal.list https://packages.lunarg.com/vulkan/1.2.189/lunarg-vulkan-1.2.189-focal.list
RUN apt-get update
RUN apt-get install -y vulkan-sdk

RUN wget https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-gpu-linux-x86_64-2.6.0.tar.gz
RUN tar -C /usr/local -xzf libtensorflow-gpu-linux-x86_64-2.6.0.tar.gz
RUN rm libtensorflow-gpu-linux-x86_64-2.6.0.tar.gz

RUN pip install -U pip
RUN pip install aqtinstall
RUN aqt install-qt linux desktop 6.2.0 gcc_64 --external 7z

ENTRYPOINT ["/bin/bash"]