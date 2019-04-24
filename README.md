The Programmer's Guide to Apache Thrift
=======================================

Source for the examples in: The Programmer's Guide to Apache Thrift

http://www.manning.com/abernethy/

The book is organized into three parts:

Part I - Apache Thrift Overview
-------------------------------

A high level introduction to Apache Thrift and its architecture. Examples from this part are hello worldish. This part also covers basic Apache Thrift setup and debugging.

Part II - Programming Apache Thrift
-----------------------------------

This part digs into each layer of the Apache Thrift framework, examining transports, protocols, types, services, servers and the Apache Thrift interface definition language in detail. Examples from these chapters use C++, Java and Python as the demonstration languages. C++ examples provide makefiles and Java examples provide Build.xml files for building with make/ant respectively. Build scripts and code  have been tested with various Apache Thrift versions. In general you should use the latest version of Apache Thrift. The Ant builds depend on SLF4J. The python examples are directly executable. You can checkout older version of this repo for examples compatible with older versions of Apache Thrift.

Part III - Apache Thrift Language Libraries
-------------------------------------------

This part of the book provides jump starts for the most popular platforms and languages used with Apache Thrift. The Web, and backend systems are examined through the lens of C++, Java, C#, JavaScript, Python, PHP, Perl and Ruby. Web chapters are complete or in-progress for Haxe, Go and Rust (code is/will-be found here). Part III also includes the final chapter, "Apache Thrift in the Enterprise", which demonstrates Apache Thrift in use with messaging systems and takes a pragmatic look at the key advantages of Apache Thrift and some of the common best practices for developing with the framework.

Tools - Miscellaneous Thrift Stuff
----------------------------------

This folder is for various Thrift related stuff. Presently only a GEdit language file for Apache Thrift IDL.

Development Environment
-----------------------

The Dockerfile in the root of this repo defines a development environment for the book which will make it easy to build and test all of the examples in the book. This file is configured to support C++, Java and Python as built but it is easy to add additional language support to the container or similarly configured system by following the instruction in the book. Apache Thrift is undergoing an important change on the way to v1.0. 

 - Switch out of the build platform (compiler and all libs) from autotools to cmake

As things migrate I will update this Dockerfile. You can "$ docker run -it randyabernethy/thrift-book" to run the prebuilt image on Docker Hub (https://hub.docker.com/r/randyabernethy/thrift-book/).

[![](https://images.microbadger.com/badges/image/randyabernethy/thrift-book.svg)](https://microbadger.com/images/randyabernethy/thrift-book "Thrift Book Layers")

