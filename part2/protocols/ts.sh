#!/bin/sh
./proto_write_times
./proto_write_times m b
./proto_write_times m c
./proto_write_times m j
rm /tmp/thrift_data 
./proto_write_times f b 
rm /tmp/thrift_data
./proto_write_times f b b
rm /tmp/thrift_data
./proto_write_times f c 
rm /tmp/thrift_data
./proto_write_times f c b
rm /tmp/thrift_data
./proto_write_times f j 
rm /tmp/thrift_data
./proto_write_times f j b

