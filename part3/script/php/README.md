PHP Examples
============

Source for the examples in: The Programmer's Guide to Apache Thrift

http://www.manning.com/abernethy/

The examples here are from the chapter 14 PHP section. 

Note: The v0.9.2 thrift compiler contains a bug which emits a php
namespace with no name(e.g. "namespace ;") when compiling
a thrift IDL file without a namespace declaration. This will be
fixed in the next release. In the meantime you can avoid this
error by declaring a namespace in your IDL (e.g. "namespace myPhpService:)
and prefixing your generated code objects with the namespace name
(e.g. "myPgpService\\...).
