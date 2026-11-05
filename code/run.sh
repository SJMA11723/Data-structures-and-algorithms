#!/bin/bash
SRC="$1"; IN="$2"; BIN="${SRC%.cpp}"
TIMEFORMAT=$'\n\nTiempo total: %R s\nUser: %U s\nSistema: %S s'
[ -n "$IN" ] && time ./"$BIN" < "$IN" || time ./"$BIN"