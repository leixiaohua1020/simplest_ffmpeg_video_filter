#! /bin/sh
g++ simplest_ffmpeg_video_filter_pure.cpp -g -o simplest_ffmpeg_video_filter_pure.exe \
-I /usr/local/include -L /usr/local/lib -lavutil -lavfilter
