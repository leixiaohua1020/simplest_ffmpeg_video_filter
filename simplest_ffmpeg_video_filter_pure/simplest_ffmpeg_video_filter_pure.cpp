/** 
 * 最简单的基于FFmpeg的AVFilter例子 - 纯净版
 * Simplest FFmpeg AVfilter Example - Pure
 *
 * 雷霄骅 Lei Xiaohua
 * leixiaohua1020@126.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 * 
 * 本程序使用FFmpeg的AVfilter实现了YUV像素数据的滤镜处理功能。
 * 可以给YUV数据添加各种特效功能。
 * 是最简单的FFmpeg的AVFilter方面的教程。
 * 适合FFmpeg的初学者。
 *
 * This software uses FFmpeg's AVFilter to process YUV raw data.
 * It can add many excellent effect to YUV data.
 * It's the simplest example based on FFmpeg's AVFilter. 
 * Suitable for beginner of FFmpeg 
 *
 */
#include <stdio.h>

#define __STDC_CONSTANT_MACROS

#ifdef _WIN32
#define snprintf _snprintf
//Windows
extern "C"
{
#include "libavfilter/avfiltergraph.h"
#include "libavfilter/buffersink.h"
#include "libavfilter/buffersrc.h"
#include "libavutil/avutil.h"
#include "libavutil/imgutils.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavfilter/avfiltergraph.h>
#include <libavfilter/buffersink.h>
#include <libavfilter/buffersrc.h>
#include <libavutil/avutil.h>
#ifdef __cplusplus
};
#endif
#endif


//const char *filter_descr = "lutyuv='u=128:v=128'";
const char *filter_descr = "boxblur";
//const char *filter_descr = "hflip";
//const char *filter_descr = "hue='h=60:s=-3'";
//const char *filter_descr = "crop=2/3*in_w:2/3*in_h";
//const char *filter_descr = "drawbox=x=100:y=100:w=100:h=100:color=pink@0.5";

int main(int argc, char* argv[])
{
    int ret;
    AVFrame *frame;
	uint8_t *frame_buffer;

    int got_frame;
	AVFilterContext *buffersink_ctx;
	AVFilterContext *buffersrc_ctx;
	AVFilterGraph *filter_graph;
	static int video_stream_index = -1;

	//Input YUV
	FILE *fp_in=fopen("sintel_480x272_yuv420p.yuv","rb+");
	if(fp_in==NULL){
		printf("Error open input file.\n");
		return -1;
	}
	int in_width=480;
	int in_height=272;

	//Output YUV
	FILE *fp_out=fopen("output.yuv","wb+");
	if(fp_out==NULL){
		printf("Error open output file.\n");
		return -1;
	}

    avfilter_register_all();

	char args[512];
	AVFilter *buffersrc  = avfilter_get_by_name("buffer");
	AVFilter *buffersink = avfilter_get_by_name("ffbuffersink");
	AVFilterInOut *outputs = avfilter_inout_alloc();
	AVFilterInOut *inputs  = avfilter_inout_alloc();
	enum PixelFormat pix_fmts[] = { PIX_FMT_YUV420P, PIX_FMT_NONE };
	AVBufferSinkParams *buffersink_params;

	filter_graph = avfilter_graph_alloc();

	/* buffer video source: the decoded frames from the decoder will be inserted here. */
	snprintf(args, sizeof(args),
		"video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
		in_width,in_height,PIX_FMT_YUV420P,
		1, 25,1,1);

	ret = avfilter_graph_create_filter(&buffersrc_ctx, buffersrc, "in",
		args, NULL, filter_graph);
	if (ret < 0) {
		printf("Cannot create buffer source\n");
		return ret;
	}

	/* buffer video sink: to terminate the filter chain. */
	buffersink_params = av_buffersink_params_alloc();
	buffersink_params->pixel_fmts = pix_fmts;
	ret = avfilter_graph_create_filter(&buffersink_ctx, buffersink, "out",
		NULL, buffersink_params, filter_graph);
	av_free(buffersink_params);
	if (ret < 0) {
		printf("Cannot create buffer sink\n");
		return ret;
	}

	/* Endpoints for the filter graph. */
	outputs->name       = av_strdup("in");
	outputs->filter_ctx = buffersrc_ctx;
	outputs->pad_idx    = 0;
	outputs->next       = NULL;

	inputs->name       = av_strdup("out");
	inputs->filter_ctx = buffersink_ctx;
	inputs->pad_idx    = 0;
	inputs->next       = NULL;

	if ((ret = avfilter_graph_parse_ptr(filter_graph, filter_descr,
		&inputs, &outputs, NULL)) < 0)
		return ret;

	if ((ret = avfilter_graph_config(filter_graph, NULL)) < 0)
		return ret;

	frame=av_frame_alloc();
	frame_buffer=(uint8_t *)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, in_width,in_height));
	avpicture_fill((AVPicture *)frame, frame_buffer, PIX_FMT_YUV420P,in_width, in_height);
	frame->width=in_width;
	frame->height=in_height;
	frame->format=PIX_FMT_YUV420P;


    while (1) {

        AVFilterBufferRef *picref;

		if(fread(frame_buffer, 1, in_width*in_height*3/2, fp_in)!= in_width*in_height*3/2){
			break;
		}
		//input Y,U,V
		frame->data[0]=frame_buffer;
		frame->data[1]=frame_buffer+in_width*in_height;
		frame->data[2]=frame_buffer+in_width*in_height*5/4;

        if (av_buffersrc_add_frame(buffersrc_ctx, frame) < 0) {
            printf( "Error while feeding the filtergraph\n");
            break;
        }

        /* pull filtered pictures from the filtergraph */
        ret = av_buffersink_get_buffer_ref(buffersink_ctx, &picref, 0);
        if (ret < 0)
            break;

        if (picref) {
			//output Y,U,V
			if(picref->format==PIX_FMT_YUV420P){
				for(int i=0;i<picref->video->h;i++){
					fwrite(picref->data[0]+picref->linesize[0]*i,1,picref->video->w,fp_out);
				}
				for(int i=0;i<picref->video->h/2;i++){
					fwrite(picref->data[1]+picref->linesize[1]*i,1,picref->video->w/2,fp_out);
				}
				for(int i=0;i<picref->video->h/2;i++){
					fwrite(picref->data[2]+picref->linesize[2]*i,1,picref->video->w/2,fp_out);
				}
			}
			printf("Process 1 frame!\n");
            avfilter_unref_bufferp(&picref);
        }

    }

	fclose(fp_in);
	fclose(fp_out);

end:
	av_frame_free(&frame);
    avfilter_graph_free(&filter_graph);

    return 0;
}


