FROM ubuntu:18.04

RUN apt update && apt install -yy gcc g++ cmake make ca-certificates

COPY . /print
WORKDIR /print

RUN mkdir _build && cd _build && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/print/_install -DBUILD_TESTS=OFF
RUN cmake --build _build
RUN cmake --build _build --target install

ENV LOG_PATH=/home/logs/log.txt
VOLUME /home/logs

WORKDIR /print/_install/bin
ENTRYPOINT ["./demo"]
