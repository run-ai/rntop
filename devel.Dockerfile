FROM ubuntu:18.04

RUN apt-get update && apt-get install -y \
    g++ \
    python3 \
    python3-pip \
    ssh \
    unzip \
&& rm -rf /var/lib/apt/lists/*

RUN wget -O bazel.sh https://github.com/bazelbuild/bazel/releases/download/4.2.1/bazel-4.2.1-installer-linux-x86_64.sh && \
    chmod +x bazel.sh && \
    ./bazel.sh && \
    rm bazel.sh

RUN pip3 install cpplint==1.5.4
