FROM ubuntu:latest
RUN apt update
RUN apt install -y gcc make
WORKDIR /app
