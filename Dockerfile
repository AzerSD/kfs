FROM debian:latest

RUN apt update && apt install -y \
    build-essential \
    xorriso \
    nasm \
    qemu-system \
    mtools \
    grub2

WORKDIR /app
COPY . /app
RUN make
CMD ["tail", "-f", "/dev/null"]
