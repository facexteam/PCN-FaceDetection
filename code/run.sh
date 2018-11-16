#!/usr/bin/en sh
export LD_LIBRARY_PATH=$CAFFEROOT/build/lib/:$LD_LIBRARY_PATH
./$1 --image ../fenghuo_faces/536.jpg --rect 344 46 257 401
