#! /bin/sh
gcc simplest_ffmpeg_video_filter.cpp -g -o simplest_ffmpeg_video_filter.out \
-I /usr/local/include -L /usr/local/lib \
-lSDLmain -lSDL -lavformat -lavcodec -lavutil -lavfilter -lswscale
