#!/bin/sh
ant
ant -Darg0=write -Darg1=bmp run
ant -Darg0=read run

thrift -gen py radio_observation.thrift
python disk_ser.py
