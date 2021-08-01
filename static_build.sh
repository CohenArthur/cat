#!/bin/sh

cd $1

make CFLAGS='-static'
