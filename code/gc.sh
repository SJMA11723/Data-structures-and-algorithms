#!/bin/bash
SRC="$1"; BIN="${SRC%.cpp}"
g++ -DLOCAL -x c++ -g -std=gnu++20 -Wunused-variable -Wall \
    -Wextra -Wshadow -fsanitize=address -fsanitize=undefined \
    -static "$SRC" -o "$BIN"