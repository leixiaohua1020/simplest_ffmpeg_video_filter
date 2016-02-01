#! /bin/sh
gcc simplest_ffmpeg_video_filter_pure.cpp -g -o simplest_ffmpeg_video_filter_pure.out \
-I /usr/local/include -L /usr/local/lib -lavutil -lavfilter
