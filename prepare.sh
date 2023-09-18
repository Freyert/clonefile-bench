#!/usr/bin/env bash

dd if=/dev/zero of=input.dat  bs=1m  count=24
gcc main.c
