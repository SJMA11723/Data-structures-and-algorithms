#!/bin/bash
SRC="$1"; BIN="${SRC%.cpp}"
g++ -x c++ -g -O2 -std=gnu++20 -static "$SRC" -o "$BIN"
