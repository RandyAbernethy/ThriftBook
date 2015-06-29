#Docker image for The Programmer's Guide to Apache Thrift
#
# To run the image from Docker Hub:
#       $ sudo docker run -it randyabernethy/thrift_book
#
# To build and run the image from within the ThriftBook dir:
#       $ sudo docker build . -t thrift_book
#       $ sudo docker run -it thrift_book

FROM ubuntu:14.04 
MAINTAINER Randy Abernethy "ra@apache.org" 

#Install C++, Java and Python dependencies
RUN apt-get update && \
    apt-get install -y \
        automake \
        bison \
        flex \
        g++ \
        git \
        libboost1.55-all-dev \
        libevent-dev \
        libssl-dev \
        libtool \
        make \
        pkg-config \
        wget \
        \
        ant \
        maven \
        openjdk-7-jdk \
        \
        python-all \
        python-all-dbg \
        python-all-dev \
        python-setuptools \
        python-support \
        python-twisted \
        python-zope.interface && \
    apt-get clean && \
    rm -rf /var/cache/apt/* && \
    rm -rf /var/lib/apt/lists/*

#Install Apache Thrift
RUN git clone http://github.com/apache/thrift &&\
    cd thrift &&\
    ./bootstrap.sh && \
    ./configure && \
    make install && \
    ldconfig

RUN git clone http://github.com/RandyAbernethy/ThriftBook
ENV PYTHONPATH=/usr/lib/python2.7/site-packages
WORKDIR /ThriftBook
CMD "/bin/bash"
