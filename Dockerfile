#Docker image for The Programmer's Guide to Apache Thrift
#
# To run the image from Docker Hub:
#       $ sudo docker run -it randyabernethy/thrift_book
#
# To build and run the image from within the ThriftBook dir:
#       $ sudo docker build -t thrift_book .
#       $ sudo docker run -it thrift_book

FROM ubuntu:16.04 
LABEL Maintainer Randy Abernethy "ra@apache.org" 

#Install C++, Java and Python dependencies
RUN apt-get update && \
    apt-get install -y \
        automake \
        bison \
        flex \
        g++ \
        git \
        libboost-all-dev \
        libevent-dev \
        libssl-dev \
        libtool \
        make \
        pkg-config \
        wget \
        \
        ant \
        maven \
        openjdk-8-jdk \
        \
        python-all \
        python-all-dbg \
        python-all-dev \
        python-setuptools \
        python-twisted \
        python-zope.interface \
        python-pip \
        python3-pip && \
    pip install --upgrade backports.ssl_match_hostname && \
    apt-get clean && \
    rm -rf /var/cache/apt/* && \
    rm -rf /var/lib/apt/lists/*

#Install Apache Thrift
RUN git clone --single-branch --branch 0.13.0 http://github.com/apache/thrift

#Fix old use of http for maven
RUN sed -i s/mvn.repo=http/mvn.repo=https/ /thrift/lib/java/gradle.properties

RUN cd thrift &&\
    ./bootstrap.sh && \
    ./configure && \
    make install && \
    ldconfig

#Fix build.xml refs to 1.0.0 to work with 0.13.0
RUN ln /thrift/lib/java/build/libs/libthrift-0.13.0.jar /usr/local/lib/libthrift-1.0.0.jar

LABEL githash e25b487
RUN git clone http://github.com/RandyAbernethy/ThriftBook
ENV PYTHONPATH=/usr/lib/python2.7/site-packages
WORKDIR /ThriftBook
CMD ["/bin/bash"]
