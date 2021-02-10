FROM debian:8

RUN apt-get update && apt-get install build-essential mingw-w64 -y

VOLUME [ "/repo" ]
WORKDIR /repo/cli

ENTRYPOINT [ "make", "CC=x86_64-w64-mingw32-gcc", "TARGET=Windows", "BIN_EXT=.exe" ]