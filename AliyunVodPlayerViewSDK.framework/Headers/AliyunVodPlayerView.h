//
//  AliyunVodPlayerView.h
//  AliyunVodPlayerViewSDK
//
//  Created by SMY on 16/9/8.
//  Copyright © 2016年 SMY. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AliyunVodPlayerViewDefine.h"
#import <AliyunVodPlayerSDK/AliyunVodPlayerDefine.h>
#import <AliyunVodPlayerSDK/AliyunVodPlayerVideo.h>
/*
 当视频返回的时候的消息响应代理，此处可以进行一些销毁操作
 */
@class AliyunVodPlayerView;
@protocol AliyunVodPlayerViewDelegate <NSObject>
/**
 * 功能：返回按钮事件
 */
- (void)onBackViewClickWithAliyunVodPlayerView:(AliyunVodPlayerView*)playerView;
- (void)aliyunVodPlayerView:(AliyunVodPlayerView*)playerView onPause:(NSTimeInterval)currentPlayTime;
- (void)aliyunVodPlayerView:(AliyunVodPlayerView*)playerView onResume:(NSTimeInterval)currentPlayTime;
- (void)aliyunVodPlayerView:(AliyunVodPlayerView*)playerView onStop:(NSTimeInterval)currentPlayTime;
- (void)aliyunVodPlayerView:(AliyunVodPlayerView*)playerView onSeekDone:(NSTimeInterval)seekDoneTime;

- (void)aliyunVodPlayerView:(AliyunVodPlayerView*)playerView lockScreen:(BOOL)isLockScreen;
- (void)aliyunVodPlayerView:(AliyunVodPlayerView*)playerView onVideoQualityChanged:(AliyunVodPlayerVideoQuality)quality;

- (void)aliyunVodPlayerView:(AliyunVodPlayerView *)playerView fullScreen:(BOOL)isFullScreen;

@end

/*
 AliyunVodPlayerView为带皮肤界面的播放器，可以直接作为View来使用
 */
@interface AliyunVodPlayerView : UIView

/*
 功能：设置AliyunVodPlayerViewDelegate代理
 */
@property (nonatomic, weak) id<AliyunVodPlayerViewDelegate> delegate;

/**
 * 功能：播放器初始化后，获取播放器是否播放。
 */
@property (nonatomic, readonly,assign)BOOL isPlaying;

/**
 * 功能：设置网络超时时间，单位毫秒
 * 备注：当播放网络流时，设置网络超时时间，默认15000毫秒
 */
@property(nonatomic, assign) int timeout;

/**
 * 功能：日志开关, default : NO
 */
@property (nonatomic, getter=isPrintLog,assign) BOOL printLog;

/*
 *************************************************
 可参考UI播放器Demo中的使用！可参考UI播放器Demo中的使用！可参考UI播放器Demo中的使用！
 *************************************************
isLockScreen 会锁定，播放器界面尺寸。
isLockPortrait yes：竖屏全屏；no：横屏全屏;
isLockScreen对isLockPortrait无效。
- (void)aliyunVodPlayerView:(AliyunVodPlayerView *)playerView lockScreen:(BOOL)isLockScreen此方法在isLockPortrait==yes时，返回的islockscreen总是yes；
isLockScreen和isLockPortrait，因为播放器时UIView，是否旋转需要配合UIViewController来控制物理旋转。
假设：支持竖屏全屏
self.playerView.isLockPortrait = YES;
self.playerView.isLockScreen = NO;
self.isLock = self.playerView.isLockScreen||self.playerView.isLockPortrait?YES:NO;

支持横屏全屏
self.playerView.isLockPortrait = NO;
self.playerView.isLockScreen = NO;
self.isLock = self.playerView.isLockScreen||self.playerView.isLockPortrait?YES:NO;

锁定屏幕
self.playerView.isLockPortrait = NO;
self.playerView.isLockScreen = YES;
self.isLock = self.playerView.isLockScreen||self.playerView.isLockPortrait?YES:NO;

self.isLock时来判定UIViewController 是否支持物理旋转。如果viewcontroller在navigationcontroller中，需要添加子类重写navigationgController中的 以下方法，根据实际情况做判定 。
*/
@property (nonatomic, assign)BOOL isLockScreen;
@property (nonatomic, assign)BOOL isLockPortrait;

/*
 功能：当前视频播放位置，单位为秒
 备注：在开始播放之后才能够获取当前播放位置。
 */
@property (nonatomic, readonly,assign)NSTimeInterval currentTime;
    
/**
 * 参数：coverUrl 图片地址。
 * 功能：封面图片。
 */
@property (nonatomic, strong)NSURL *coverUrl;


/**
 * 功能：获取缓冲的时长，只读属性，单位为毫秒。
 * 备注：当调用了prepareToPlay后，并且开始播放后，才能获取该值。
 */
@property(nonatomic, readonly)  NSTimeInterval bufferPercentage;

/*
 功能：初始化窗口大小
 参数：frame:视图view大小
 备注：默认皮肤为蓝色
 */
- (instancetype)initWithFrame:(CGRect)frame;

/*
 功能：初始化窗口大小，并且设置播放器窗口皮肤
 参数：
    frame:视图view大小
    skin: 皮肤样式，类型有：
        AliyunVodPlayerViewSkinBlue,
        AliyunVodPlayerViewSkinRed,
        AliyunVodPlayerViewSkinOrange,
        AliyunVodPlayerViewSkinGreen
 */
- (instancetype)initWithFrame:(CGRect)frame andSkin:(AliyunVodPlayerViewSkin)skin;


/*
 *功能：临时AccessKeyId、AccessKeySecret和SecurityToken：开启RAM授权，并通过STS授权系统提供的OpenAPI或SDK获取的AccessKeyId、AccessKeySecret和SecurityToken，用于播放和下载请求
 *备注：参数明细->https://help.aliyun.com/document_detail/28788.html?spm=5176.doc28787.6.706.2G5SLS
 *版本：3.2.0版本使用
 */
- (void)playViewPrepareWithVid:(NSString *)vid accessKeyId:(NSString*)accessKeyId accessKeySecret:(NSString*)accessKeySecret securityToken:(NSString *)securityToken;

/*
 *功能：使用vid+playauth方式播放。
 *参数：playKey 播放凭证
 vid 视频id
 *备注：本地视频播放，AliyunVodPlayerManagerDelegate在AliyunVodPlayerEventPrepareDone 状态下，某些参数无法获取（如：视频标题、清晰度）
 userPlayKey :1.2.0之前版本参数名称 apikey。
 
 *playauth获取方法：https://help.aliyun.com/document_detail/52881.html?spm=5176.doc52879.6.650.aQZsBR
 
 客户端开发也可以通过python脚本获取播放凭证进行调试，具体流程如下：
 安装python2.7+pip环境（Mac环境下自带，Windows环境自行安装）
 使用终端安装SDK，运行以下命令：
 pip install aliyun-python-sdk-core
 pip install aliyun-python-sdk-vod
 下载Python脚本，从阿里云控制台获取accessKeyId和accessKeySecret并替换脚本里面的字段内容，从点播控制台获取已经上传视频的videoID并替换脚本里面的字段内容。
 在python脚本所在目录下通过终端执行以下命令：
 python playAuth.py
 在终端中查看获取的PlayAuth和VideoId。
 在播放器SDK中使用获取的PlayAuth和VideoId进行播放，注意PlayAuth的时效为100秒，如果过期请重新获取。
 
 */
- (void)playViewPrepareWithVid:(NSString *)vid playAuth : (NSString *)playAuth;

/*
 *功能：播放器初始化视频，主要目的是分析视频内容，读取视频头信息，解析视频流中的视频和音频信息，并根据视频和音频信息去寻找解码器，创建播放线程等
 *参数：url，输入的url，包括本地地址和网络视频地址
 *备注：调用该函数完成后立即返回，需要等待准备完成通知，收到该通知后代表视频初始化完成，视频准备完成后可以获取到视频的相关信息。
 使用本地地址播放，注意用户需要传 NSURL 类型数据，不是NSSting 类型数据。
 本地视频播放，AliyunVodPlayerManagerDelegate在AliyunVodPlayerEventPrepareDone 状态下，某些参数无法获取（如：视频标题、清晰度）
 */
- (void)playViewPrepareWithURL:(NSURL *)url;

/*
 *功能：视频转码服务用户使用播放方式
 *参数：部分参数参考:https://help.aliyun.com/document_detail/53522.html?spm=5176.doc53534.2.5.mhSfOh
       HLS标准加密:https://help.aliyun.com/document_detail/59885.html?spm=5176.product29194.6.607.2bynDX
 *备注：
 */
- (void)playViewPrepareWithVid:(NSString *)vid
                     accessId : (NSString *)accessId
                 accessSecret : (NSString *)accessSecret
                     stsToken : (NSString *)stsToken
                     autoInfo : (NSString *)autoInfo
                       region : (NSString *)region
                   playDomain : (NSString *)playDomain
                mtsHlsUriToken:(NSString *)mtsHlsUriToken;

/*
 功能：设置是否自动播放
 参数：
    autoPlay：YES为自动播放
 */
- (void)setAutoPlay:(BOOL)autoPlay;


/*
 功能：开始播放视频
 备注：在prepareWithVid之后可以调用start进行播放。
 */
- (void)start;

/*
 功能：停止播放视频
 */
- (void)stop;

/*
 功能：暂停播放视频
 */
- (void)pause;

/*
 功能：继续播放视频，此功能应用于pause之后，与pause功能匹配使用
 */
- (void)resume;

/*
 功能：重播
 */
- (void)replay;

/*
 功能：释放播放器
 */
- (void)releasePlayer;

/*
 AliyunVodPlayerStateIdle = 0,           //空转，闲时，静态
 AliyunVodPlayerStateError,              //错误
 AliyunVodPlayerStatePrepared,           //已准备好
 AliyunVodPlayerStatePlay,               //播放
 AliyunVodPlayerStatePause,              //暂停
 AliyunVodPlayerStateStop,               //停止
 AliyunVodPlayerStateFinish,             //播放完成
 AliyunVodPlayerStateLoading             //加载中
 */
- (AliyunVodPlayerState)playerViewState;

/**
 * 功能：声音调节,调用系统MPVolumeView类实现，并非视频声音;volume(0~1.0)
 */
- (void)setVolume:(float)volume;

/**
 * 功能：亮度,调用brightness系统属性，brightness(0~1.0)
 */
- (void)setBrightness :(float)brightness;


/**
 * 功能：循环播放控制
 */
@property(nonatomic, readwrite)  BOOL circlePlay;

/**
 * 功能：截取当前正在播放图像
 */
-(UIImage*) snapshot;

/*
 功能：获取此播放器版本号
 */
- (NSString*) getSDKVersion;
    
/*
 功能：隐藏,后续改进隐藏方案;yes：隐藏所有功能按钮界面。
 */
- (void)setBackViewHidden:(BOOL)hidden ;
    
/*
 功能：设置标题
 */
- (void)setTitle:(NSString *)title ;

/**
 * 功能：获取媒体信息, 当AliyunVodPlayerEventPrepareDone时，才能获取到该参数对象
 */
- (AliyunVodPlayerVideo *)getAliyunMediaInfo;

/**
 * 功能：
 * 参数：block:音频数据回调
 *
 */
-(void) getAudioData:(void (^)(NSData *data))block;
/**
 * 功能：设置边播边缓存功能
 * 参数：bEnabled:是否开启缓存功能
 *      saveDir:缓存存储的路径
 *      maxSize:缓存路径最大空间
 *      maxDuration:缓存最大视频最大长度
 */
-(void) setPlayingCache:(BOOL)bEnabled saveDir:(NSString*)saveDir maxSize:(int64_t)maxSize maxDuration:(int)maxDuration;


/**
 * 功能：播放器播放结束，文字描述；
 * 参数：默认文案：@"再次观看，请点击重新播放";
 */
-(void)setPlayFinishDescribe:(NSString *)des;

/**
 * 功能：播放器网络状态不好，文字描述；
 * 参数：默认文案：@"当前网络不佳，请稍后点击重新播放";
 */
-(void)setNetTimeOutDescribe:(NSString *)des;

/**
 * 功能：播放器无网络，文字描述；
 * 参数：默认文案：@"无网络连接，检查网络后点击重新播放";
 */
-(void)setNoNetDescribe:(NSString *)des;

/**
 * 功能：播放器加载出错，文字描述；
 * 参数：默认文案：@"视频加载出错，请点击重新播放";
 */
-(void)setLoaddataErrorDescribe:(NSString *)des;

/**
 * 功能：播放器4G网络状态，文字描述；
 * 参数：默认文案：@"当前为移动网络，请点击播放";
 */
-(void)setUseWanNetDescribe:(NSString *)des;

@end
