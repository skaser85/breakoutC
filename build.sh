#! /bin/bash

gcc -o test test.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./test
