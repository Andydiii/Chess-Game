#!/bin/bash

tot=""
for f in $(ls *.cc); do
    tot="${tot} ${f:0:-3}.o"
    # tot="${tot} ${f}"
done
echo ${tot}
