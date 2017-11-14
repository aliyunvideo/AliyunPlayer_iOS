
/*
 *
 * This framework uses FFmpeg source code.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 */


#import <Foundation/Foundation.h> 
#import <UIKit/UIKit.h>
#import "AliVcPlayerErrorCode.h"

#define ALIVC_EXTERN     extern __attribute__((visibility ("default")))

/**
 *  播放器通知定义
 
 *   AliVcMediaPlayerLoadDidPreparedNotification：播放器初始化视频文件完成通知，调用prepareToPlay函数，会发送该通知，代表视频文件已经准备完成，此时可以在这个通知中获取到视频的相关信息，如视频分辨率，视频时长等。
 
 *   AliVcMediaPlayerPlaybackDidFinishNotification：播放完成通知，当视频正常播放完成后会收此通知。
 
 *   AliVcMediaPlayerPlaybackStopNotification：当前调用播放器Stop接口时会收到此通知。
 
 *   AliVcMediaPlayerStartCachingNotification:播放器开始缓冲视频时发送该通知，当播放网络文件时，网络状态不佳或者调用seekTo时，此通知告诉用户网络下载数据已经开始缓冲。
 
 *   AliVcMediaPlayerEndCachingNotification:播放器结束缓冲视频时发送该通知，当数据已经缓冲完，告诉用户已经缓冲结束，来更新相关UI显示。
 
 *   AliVcMediaPlayerPlaybackErrorNotification:播放器播放失败发送该通知，并在该通知中可以获取到错误码。
 
 *   AliVcMediaPlayerSeekingDidFinishNotification:播放器位置改变完成后发送该通知。
 
 *   AliVcMediaPlayerFirstFrameNotification:播放器状态首帧显示后发送的通知。

 播放器通知发送逻辑：
    1.	调用prepareToPlay成功后发送AliVcMediaPlayerLoadDidPreparedNotification通知，失败则会发送AliVcMediaPlayerPlaybackErrorNotification。
    2.	调用play、pause、stop、prepareToPlay、seekTo失败后发送AliVcMediaPlayerPlaybackErrorNotification通知。
    3.	调用stop/reset成功后播放视频结束发送AliVcMediaPlayerPlaybackStopNotification通知
    4.  播放器自动播放结束会发送AliVcMediaPlayerPlaybackDidFinishNotification通知。
    5.	调用seekTo成功后发送AliVcMediaPlayerSeekingDidFinishNotification通知。
    6.  AliVcMediaPlayerStartCachingNotification和AliVcMediaPlayerEndCachingNotification通知，这个是在网络视频缓冲数据不足以够播放后会发送此通知，一般网络视频在调用seekTo后会发送此通知。
 */
ALIVC_EXTERN NSString * const AliVcMediaPlayerLoadDidPreparedNotification;
ALIVC_EXTERN NSString * const AliVcMediaPlayerPlaybackDidFinishNotification;
ALIVC_EXTERN NSString * const AliVcMediaPlayerPlaybackStopNotification;
ALIVC_EXTERN NSString * const AliVcMediaPlayerStartCachingNotification;
ALIVC_EXTERN NSString * const AliVcMediaPlayerEndCachingNotification;
ALIVC_EXTERN NSString * const AliVcMediaPlayerPlaybackErrorNotification;
ALIVC_EXTERN NSString * const AliVcMediaPlayerSeekingDidFinishNotification;
ALIVC_EXTERN NSString * const AliVcMediaPlayerFirstFrameNotification;


/**
 *  播放器媒体类型
 *  播放器播放是直播还是点播类型枚举类型设置
 */
enum {
    MediaType_AUTO = -1,
    MediaType_VOD = 0,
    MediaType_LIVE = 1
};
typedef NSInteger MediaType;


/**
 * 适应全屏还是充满全屏
 * 备注：scalingModeApsectFill可能会存在crop的情况
 */
enum {
    scalingModeAspectFit = 0,
    scalingModeAspectFitWithCropping = 1,
};
typedef NSInteger ScalingMode;


//调试信息的key指，用于接口getAllDebugInfo信息返回值的dictionary的key的值
//视频解码帧率，double值
#define FLT_VIDEO_DECODE_FPS @"dec-fps"

//视频下载帧率，double值
#define FLT_VIDEO_OUTPUT_FPS @"out-fps"

//视频stream index值，int64值
#define INT64_SELECT_VIDEO_STREAM @"select_v"

//音频stream index值，int64值
#define INT64_SELECT_AUDIO_STREAM @"select_a"

//视频缓冲的长度，int64值
#define INT64_VIDEO_CACHE_DURATION @"vcache-dur"

//音频缓冲的长度，int64值
#define INT64_AUDIO_CACHE_DURATION @"acache-dur"

//视频缓冲的字节数，int64值
#define INT64_VIDEO_CACHE_BYTES @"vcache-bytes"

//音频缓冲的字节数，int64值
#define INT64_AUDIO_CACHE_BYTES @"acache-bytes"

//视频缓冲的packet个数，int64值
#define INT64_VIDEO_CACHE_PACKETS @"vcache-pkts"

//音频缓冲的packet个数，int64值
#define INT64_AUDIO_CACHE_PACKETS @"acache-pkts"

//视频首帧显示时间，double值
#define FLT_1ST_VFRAME_SHOW @"1st-vframeshow"

//视频find stream info的时间
#define FLT_FIND_STREAM_TIME @"find-stream"

//视频open format 的时间
#define FLT_OPEN_FORMAT_TIME @"open-format"

//视频tcp dns解析的时间
#define FLT_TCP_DNS_TIME @"tcp-dns-time"

//视频tcp connect解析的时间
#define FLT_TCP_CONNECT_TIME @"tcp-connect-time"

//视频rtmp open解析的时间
#define FLT_RTMP_OPEN_TIME @"rtmp-open-time"

//视频http open解析的时间
#define FLT_HTTP_OPEN_TIME @"http-open-time"
