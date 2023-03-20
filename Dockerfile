# Build command bellow:
# docker build --build-arg username=$USER --build-arg uid=`id -u $USER` .
FROM registry.access.redhat.com/ubi8:8.7-1090

RUN dnf install -y cmake gcc-c++ gcc python39-devel git

WORKDIR /app

# STUB TODO
