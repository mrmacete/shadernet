#!/bin/bash

HEADER_FILE=/home/macete/cprojects/shadernet/src/playground/header

for i in "$@"
do
	cat $HEADER_FILE $i > $i.new
	mv -f $i.new $i	
done
