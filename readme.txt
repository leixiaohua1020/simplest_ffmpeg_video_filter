最简单的基于FFmpeg的AVFilter例子
Simplest FFmpeg AVfilter Example

雷霄骅 Lei Xiaohua
leixiaohua1020@126.com
中国传媒大学/数字电视技术
Communication University of China / Digital TV Technology
http://blog.csdn.net/leixiaohua1020
 
 
本程序使用包含下面两个项目：
simplest_ffmpeg_video_filter：可以将一张PNG图片作为水印叠加到视频上，结合使用了libavfilter，libavcodec等类库。
simplest_ffmpeg_video_filter_pure：可以给YUV像素数据加特效，只用了libavfilter库。


This project contains 2 projects:
simplest_ffmpeg_video_filter: Put a PNG picture as watermark to a video file, use some libraries such as libavfilter and libavcodec.
simplest_ffmpeg_video_filter_pure：Add excellent effect to YUV raw data, only use libavfilter.