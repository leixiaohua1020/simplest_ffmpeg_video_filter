#! /bin/sh
#最简单的基于FFmpeg的AVFilter例子（叠加水印） ----MinGW命令行编译
#Simplest FFmpeg AVfilter Example (Watermark)----Compile in MinGW 
#
#雷霄骅 Lei Xiaohua
#leixiaohua1020@126.com
#中国传媒大学/数字电视技术
#Communication University of China / Digital TV Technology
#http://blog.csdn.net/leixiaohua1020
#
#compile
g++ simplest_ffmpeg_video_filter.cpp -g -o simplest_ffmpeg_video_filter.exe \
-I /usr/local/include -L /usr/local/lib \
-lmingw32 -lSDLmain -lSDL -lavformat -lavcodec -lavutil -lavfilter -lswscale
