#! /bin/bash

gcc -o ./bin/breakout test.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 &&
  ./bin/breakout
