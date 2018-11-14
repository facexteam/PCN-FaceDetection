#!/usr/bin/en sh
export LD_LIBRARY_PATH=$CAFFEROOT/build/lib/:$LD_LIBRARY_PATH
./$1 --image ../fenghuo_faces/0.jpg --rect 462 152 83 95 --image ../fenghuo_faces/556.jpg --rect 44 14 56 72
