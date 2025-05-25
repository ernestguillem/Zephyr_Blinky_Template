# CLion remote docker environment.
#
# Build and run:
#   docker build -t arm_gcc_sa -f Dockerfile .
#   docker run --rm -v {Folder where the project is}:/home -t arm_gcc_sa:latest "command to execute"
#   docker run --rm -v {Folder where the project is}:/home -t arm_gcc_sa:latest "command to execute"
#   This container stops and deletes itself after the execution of the command
#
#   To open a terminal on the current directory
#   docker run --rm -v $(PWD):/home -it arm_gcc_sa:latest bash

FROM debian:12-slim

RUN DEBIAN_FRONTEND="noninteractive" apt-get update && apt-get -y install tzdata

RUN DEBIAN_FRONTEND="noninteractive" apt-get --no-install-recommends install -y  \
  git  \
  cmake  \
  ninja-build  \
  gperf \
  ccache  \
  dfu-util  \
  device-tree-compiler  \
  wget \
  python3-dev  \
  python3-pip  \
  python3-setuptools  \
  python3-tk  \
  python3-wheel  \
  xz-utils  \
  file \
  make  \
  gcc  \
  libsdl2-dev  \
  libmagic1 \
  python3-venv \
&& apt-get clean

RUN python3 -m venv ~/zephyrproject/.venv

RUN ~/zephyrproject/.venv/bin/pip install west

# NOT SURE IF THESE COMMANDS ARE NECESSARY IF WE USE A CUSTOME west.yml
# RUN ~/zephyrproject/.venv/bin/west init ~/zephyrproject
# RUN cd ~/zephyrproject && ~/zephyrproject/.venv/bin/west update



# RUN gem install ceedling
# RUN gem install ceedling

# Install ARM_GCC compiler 14.2rel1
# RUN cd /toolchain \
#   && wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz \
#   && tar xvf arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz \
#   && rm arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi.tar.xz \
#   && rm -rf /toolchain/arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi/share/doc

# Set all folders in docker as safe for git
# RUN git config --system --add safe.directory '*'

# Set up the compiler environment path
# ENV ARMGCC_DIR=/toolchain/arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi/bin
# ENV PATH="${PATH}:/toolchain/arm-gnu-toolchain-14.2.rel1-aarch64-arm-none-eabi/bin"

# Settings for using clang instead of gcc. Need to install clang in apt-get
# RUN update-alternatives --install /usr/bin/c++ c++ /usr/bin/clang++ 100
# RUN update-alternatives --install /usr/bin/cc cc /usr/bin/clang 100

WORKDIR /home
