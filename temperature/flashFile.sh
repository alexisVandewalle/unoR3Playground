#!/bin/bash

TARGET=m328p
FILE=$1
PROGRAMMER=arduino
PORT=/dev/ttyACM0

avrdude -p $TARGET -c $PROGRAMMER -P $PORT -e -U flash:w:$FILE
