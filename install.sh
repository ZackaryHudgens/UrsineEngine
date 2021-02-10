#!/bin/bash

# Copy the installed files to /usr/local.
if [ ! -d /usr/local/lib/UrsineEngine ];
  then
    mkdir /usr/local/lib/UrsineEngine
  else
    rm -rf /usr/local/lib/UrsineEngine/*
fi

if [ ! -d /usr/local/include/UrsineEngine ];
  then
    mkdir /usr/local/include/UrsineEngine
  else
    rm -rf /usr/local/include/UrsineEngine/*
fi

cp -R install/lib/* /usr/local/lib/UrsineEngine
cp -R install/include/* /usr/local/include/UrsineEngine
