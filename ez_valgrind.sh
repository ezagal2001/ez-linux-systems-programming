#!/bin/bash
# This script runs valgrind with the tool memcheck on
# the first argument passed to it.
#
echo "Running the program $(basename "$0")"

valgrind --tool=memcheck "$1"

exit

