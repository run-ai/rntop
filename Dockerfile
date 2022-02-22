FROM ubuntu:20.04

RUN apt update && apt install -y \
    libncurses5-dev \
    libssh-dev \
    openssh-client \
&& rm -rf /var/lib/apt/lists/*

COPY rntop /rntop

ENTRYPOINT ["/rntop"]
