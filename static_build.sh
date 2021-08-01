#!/bin/sh

cd $1

make CFLAGS='-static'
cp cat static_cat
