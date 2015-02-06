#! /bin/sh
#最简单的基于FFmpeg的AVFilter例子（叠加水印）----命令行编译
#Simplest FFmpeg AVfilter Example (Watermark)----Compile in Shell 
#
#雷霄骅 Lei Xiaohua
#leixiaohua1020@126.com
#中国传媒大学/数字电视技术
#Communication University of China / Digital TV Technology
#http://blog.csdn.net/leixiaohua1020
#
#compile
gcc simplest_ffmpeg_video_filter.cpp -g -o simplest_ffmpeg_video_filter.out \
-I /usr/local/include -L /usr/local/lib \
-lSDLmain -lSDL -lavformat -lavcodec -lavutil -lavfilter -lswscale


