#! /bin/sh
g++ simplest_ffmpeg_video_filter.cpp -g -o simplest_ffmpeg_video_filter.exe \
-I /usr/local/include -L /usr/local/lib \
-lmingw32 -lSDLmain -lSDL -lavformat -lavcodec -lavutil -lavfilter -lswscale
