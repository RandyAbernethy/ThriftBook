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

This part digs into each layer of the Apache Thrift framework, examining transports, protocols, types, servers and the Apache Thrift interface definition language in detail. Examples from these chapters use C++, Java and Python as the demonstration languages. C++ examples provide make files and Java examples provide Build.xml files for building with make and ant respectively. All build scripts depend on Apache Thrift v1.0 (or the dev trunk). The Ant builds depend on SLF4J v1.7.12, to use other versions you can simply edit the Build.xml. The python examples are directly executable.

Part III - Polygot Application Development
------------------------------------------

This part of the book provides jump starts for the most popular platforms and languages used with Apache Thrift. The Web, Mobile, and backend systems are examined through the lens of C++, Java, C#, JavaScript, Python, PHP, Perl, Ruby and Swift. The general idea is to add jump starts for every Apache Thrift language over time, though only the above mentioned languages will be in the first edition of the book. In addition to the above mentioned languages the Haxe jumpstart is complete and available as an online addition with examples in this repo.

There is a lager enterprise style application originally designed as a vehicle for this part of the book but it was not included in the final text due to length restrictions. I will post the code here in the future if there is interest.

Tools - Miscellaneous Thrift Stuff
----------------------------------

This folder is for various Thrift related stuff. Presently only a GEdit language file for Apache Thrift IDL.

Development Environment
-----------------------

A Dockerfile in the root of this repo will ultimately define a development environment for the book which will make it easy to build and test all of the examples in the book as well as the extensions provided here. This file is just a stub presently. Apache Thrift is undergoing three important changes on the way to the imminent v1.0. 
 - Support for Python 3.x
 - Support for C++11
 - Building the platform (compiler and all libs) with cmake
As things stabilize I will update this Dockerfile.
