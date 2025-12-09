#!/bin/bash
# Script to run Minesweeper in a terminal with lldb
cd "$(dirname "$0")"
export TERM=xterm-256color
lldb "${PWD}/build/Minesweper"

