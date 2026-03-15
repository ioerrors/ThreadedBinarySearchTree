FROM mcr.microsoft.com/devcontainers/cpp:1-debian-12

RUN apt-get update && apt-get install -y \
    cmake \
    ninja-build \
    gdb \
    lldb \
    clang \
    clangd \
    clang-tidy \
    clang-format \
    valgrind \
 && rm -rf /var/lib/apt/lists/*
