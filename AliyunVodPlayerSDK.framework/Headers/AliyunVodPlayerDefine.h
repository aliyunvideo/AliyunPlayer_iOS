//
//  AliyunVodPlayerDefine.h
//  AliyunVodPlayerSDK
//
//  Created by SMY on 16/8/31.
//  Copyright © 2016年 SMY. All rights reserved.
//


typedef NS_ENUM(int, AliyunVodPlayerVideoQuality) { //视频质量
    AliyunVodPlayerVideoFD = 0,        // 流畅
    AliyunVodPlayerVideoLD,            // 标清
    AliyunVodPlayerVideoSD,            // 高清
    AliyunVodPlayerVideoHD,            // 超清
    AliyunVodPlayerVideo2K,            // 2K
    AliyunVodPlayerVideo4K,            // 4K
    AliyunVodPlayerVideoOD,            // 原画
};

typedef NS_ENUM(int, AliyunVodPlayerEvent) {       //视频事件回馈
    AliyunVodPlayerEventPrepareDone,
    AliyunVodPlayerEventPlay,
    AliyunVodPlayerEventFirstFrame,
    AliyunVodPlayerEventPause,
    AliyunVodPlayerEventStop,
    AliyunVodPlayerEventFinish,
    AliyunVodPlayerEventBeginLoading,
    AliyunVodPlayerEventEndLoading,
    AliyunVodPlayerEventSeekDone
};

typedef NS_ENUM(int, AliyunVodPlayerDisplayMode) {  //浏览方式
    AliyunVodPlayerDisplayModeFit = 0,            // 保持原始比例
    AliyunVodPlayerDisplayModeFitWithCropping // 全屏占满屏幕
};

typedef NS_ENUM(int , AliyunVodRequestMethod) {
    AliyunVodRequestMethodPlayAuth = 0,
    AliyunVodRequestMethodStsToken,
};


typedef NS_ENUM(int, AliyunVodPlayerState) {  //视频状态
    AliyunVodPlayerStateIdle = 0,           //空转，闲时，静态
    AliyunVodPlayerStateError,              //错误
    AliyunVodPlayerStatePrepared,           //已准备好
    AliyunVodPlayerStatePlay,               //播放
    AliyunVodPlayerStatePause,              //暂停
    AliyunVodPlayerStateStop,               //停止
    AliyunVodPlayerStateFinish,             //播放完成
    AliyunVodPlayerStateLoading             //加载中
};

