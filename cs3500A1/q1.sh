#!/bin/bash


read target
let count=0
for f in "$target"/*
do
    echo $(basename $f)
    let count=count+1
done
echo ""
echo "Count: $count"
