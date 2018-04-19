//
//  AliyunVodPlayerManager.h
//  AliyunVodPlayerSDK
//
//  Created by 王凯 on 2017/8/4.
//  Copyright © 2017年 SMY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "AliyunVodPlayerVideo.h"
#import "AliyunVodPlayerDefine.h"
#import <AliyunPlayerSDK/AliyunPlayerSDK.h>

@class AliyunVodPlayer;

/**
 * 功能：播放事件协议方法
 */
@protocol AliyunVodPlayerDelegate <NSObject>

@required
/**
 * 功能：播放事件协议方法,主要内容 AliyunVodPlayerEventPrepareDone状态下，此时获取到播放视频数据（时长、当前播放数据、视频宽高等）
 * 参数：event 视频事件
 */
- (void)vodPlayer:(AliyunVodPlayer *)vodPlayer onEventCallback:(AliyunVodPlayerEvent)event ;

/**
 * 功能：播放器播放时发生错误时，回调信息
 * 参数：errorModel 播放器报错时提供的错误信息对象
 */
- (void)vodPlayer:(AliyunVodPlayer *)vodPlayer playBackErrorModel:(AliyunPlayerVideoErrorModel *)errorModel;

@optional

/**
 * 功能：播放器播放即将切换清晰度时
 * 参数：quality ： vid+playauth播放方式、vid+sts播放方式时的清晰度
        videoDefinition ： 媒体转码播放方式的清晰度
 */
- (void)vodPlayer:(AliyunVodPlayer*)vodPlayer willSwitchToQuality:(AliyunVodPlayerVideoQuality)quality videoDefinition:(NSString*)videoDefinition;

/**
 * 功能：播放器播放切换清晰度完成
 * 参数：quality ： vid+playauth播放方式、vid+sts播放方式时的清晰度
 videoDefinition ： 媒体转码播放方式的清晰度
 */
- (void)vodPlayer:(AliyunVodPlayer *)vodPlayer didSwitchToQuality:(AliyunVodPlayerVideoQuality)quality videoDefinition:(NSString*)videoDefinition;

/**
 * 功能：播放器播放切换清晰度失败
 * 参数：quality ： vid+playauth播放方式、vid+sts播放方式时的清晰度
 videoDefinition ： 媒体转码播放方式的清晰度
 */
- (void)vodPlayer:(AliyunVodPlayer*)vodPlayer failSwitchToQuality:(AliyunVodPlayerVideoQuality)quality videoDefinition:(NSString*)videoDefinition;

/**
 * 功能：1.播放器设置了循环播放，此代理方法才会有效。2.播放器播放完成后，开始循环播放后，此协议被调用
 */
- (void)onCircleStartWithVodPlayer:(AliyunVodPlayer*)vodPlayer;

/*
 *功能：播放器请求时，通知用户传入的参数鉴权过期。
 */
- (void)onTimeExpiredErrorWithVodPlayer:(AliyunVodPlayer *)vodPlayer;

/*
 *功能：播放地址将要过期时，提示用户当前播放地址过期。 （策略：当前播放器地址过期时间2小时，我们在播放地址差1分钟过期时提供回调；（7200-60）秒时发送）
 *参数：videoid：将过期时播放的videoId
 *参数：quality：将过期时播放的清晰度，playauth播放方式和STS播放方式有效。
 *参数：videoDefinition：将过期时播放的清晰度，MPS播放方式时有效。
 */
- (void)vodPlayerPlaybackAddressExpiredWithVideoId:(NSString *)videoId quality:(AliyunVodPlayerVideoQuality)quality videoDefinition:(NSString*)videoDefinition;


@end

/**
 * ALPlayerManager为播放器管理类，实现播放器的各种控制
 */
@interface AliyunVodPlayer : NSObject

/*
 *功能：防盗链参数
 */
@property (nonatomic, copy) NSString *referer;

/*
 *功能：临时AccessKeyId、AccessKeySecret和SecurityToken：开启RAM授权，并通过STS授权系统提供的OpenAPI或SDK获取的AccessKeyId、AccessKeySecret和SecurityToken，用于播放和下载请求
 *备注：参数明细->https://help.aliyun.com/document_detail/28788.html?spm=5176.doc28787.6.706.2G5SLS
 *版本：3.2.0版本使用
 */
- (void)prepareWithVid:(NSString *)vid
           accessKeyId:(NSString *)accessKeyId
       accessKeySecret:(NSString *)accessKeySecret
         securityToken:(NSString *)securityToken;



/*
 *功能：使用vid+playauth方式播放。
 *参数：vid 视频id
 
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
- (void)prepareWithVid:(NSString *)vid
              playAuth:(NSString *)playAuth;

/*
 *功能：视频转码服务用户使用播放方式
 *参数：部分参数参考:https://help.aliyun.com/document_detail/53522.html?spm=5176.doc53534.2.5.mhSfOh
       HLS标准加密:https://help.aliyun.com/document_detail/59885.html?spm=5176.product29194.6.607.2bynDX
 *备注：
 */
- (void)prepareWithVid:(NSString*)vid
                 accId:(NSString *)accId
             accSecret:(NSString*)accSecret
              stsToken:(NSString*)stsToken
              authInfo:(NSString*)authInfo
                region:(NSString*)region
            playDomain:(NSString*)playDomain
        mtsHlsUriToken:(NSString*)mtsHlsUriToken;

/*
 *功能：播放器初始化视频，主要目的是分析视频内容，读取视频头信息，解析视频流中的视频和音频信息，并根据视频和音频信息去寻找解码器，创建播放线程等
 *参数：url，输入的url，包括本地地址和网络视频地址
 *备注：调用该函数完成后立即返回，需要等待准备完成通知，收到该通知后代表视频初始化完成，视频准备完成后可以获取到视频的相关信息。
 使用本地地址播放，注意用户需要传 NSURL 类型数据，不是NSSting 类型数据。
 */
- (void)prepareWithURL:(NSURL *)url;

/*
 功能：获取播放器当前播放状态
 当前播放状态有：
 AliyunVodPlayerStateIdle = 0,           //空转，闲时，静态
 AliyunVodPlayerStateError,              //错误
 AliyunVodPlayerStatePrepared,           //已准备好
 AliyunVodPlayerStatePlay,               //播放
 AliyunVodPlayerStatePause,              //暂停
 AliyunVodPlayerStateStop,               //停止
 AliyunVodPlayerStateFinish,             //播放完成
 AliyunVodPlayerStateLoading             //加载中
 */
- (AliyunVodPlayerState)playerState;


/*
 功能：开始播放视频
 备注：在prepareWithVid之后可以调用start进行播放。
 */
- (void)start;

/*
 功能：恢复播放视频
 备注：在pause暂停视频之后可以调用resume进行播放。
 */
- (void)resume;

/*
 功能：暂停播放视频
 备注：在start播放视频之后可以调用pause进行暂停。
 */
- (void)pause;

/*
 功能：停止播放视频
 */
- (void)stop;

/**
 * 功能：重置播放器，其目的是将播放器所有状态恢复到最初位置，当播放器内部出现错误或其它问题时，调用此函数来进行恢复。
 * 备注：该函数和stop函数的区别是，reset也能够实现stop的功能，但是reset会去销毁播放器内部的各种变量，然后重新进行变量初始化，view变量等会被设置成空。
 */
- (void)reset;

/*
 功能：重播，重新播放上一次url地址视频。
 */
- (void)replay;

/*
 功能：销毁播放器
 */
- (void)releasePlayer;

/*
 功能：跳转到指定位置进行播放，单位为秒
 备注：在播放器状态AliyunVodPlayerEventFirstFrame之后才能调用此函数。
 */
- (void)seekToTime:(NSTimeInterval)time;

/**
 * 功能：获取媒体信息, 当AliyunVodPlayerEventPrepareDone时，才能获取到该参数对象
  */
- (AliyunVodPlayerVideo *)getAliyunMediaInfo;


/**
 * 功能：设置边播边缓存功能
 * 参数：bEnabled:是否开启缓存功能
 *      saveDir:缓存存储的路径   
 *      maxSize:缓存路径最大空间         单位：MB
 *      maxDuration:缓存最大视频最大长度  单位 ： 秒
 */
-(void) setPlayingCache:(BOOL)bEnabled saveDir:(NSString*)saveDir maxSize:(int64_t)maxSize maxDuration:(int)maxDuration;

/**
 * 功能：
 * 参数：设置渲染视图角度
 */
-(void) setRenderRotate:(RenderRotate)rotate;

/**
 * 功能：
 * 参数：设置渲染镜像
 */
-(void) setRenderMirrorMode:(RenderMirrorMode)mirrorMode;

/**
 * AliyunVodPlayerManagerDelegate 播放器代理
 */
@property (nonatomic ,weak) id<AliyunVodPlayerDelegate> delegate;

/**
 * 功能：获取视频显示的窗口，
 * 备注：此窗口为内部创建的窗口，用户可以用来添加到用户界面上进行显示
 */
@property (nonatomic, assign, readonly) UIView *playerView;

/**
 * 功能：设置/获取是否自动播放
 * 备注：如果设置成自动播放，则prepareWithVid之后不需要调用start进行播放
 */
@property (nonatomic, getter=isAutoPlay) BOOL autoPlay;

/**
 * 功能：获取/设置显示模式
 * 显示模式有： AliyunVodPlayerDisplayModeFit,            // 保持原始比例
              AliyunVodPlayerDisplayModeFitWithCropping // 全屏占满屏幕
 */
@property (nonatomic,assign) AliyunVodPlayerDisplayMode displayMode;

/**
 * 功能：设置是否静音，YES为静音
 */
@property (nonatomic, getter=isMuteMode) BOOL muteMode;

/**
 * 功能：播放器初始化后，获取播放器是否播放。
 */
@property (nonatomic, readonly,assign) BOOL isPlaying;

/**
 * 功能：设置网络超时时间，单位毫秒
 * 备注：当播放网络流时，设置网络超时时间，默认15000毫秒
 */
@property(nonatomic, assign) int timeout;

/*
 功能：视频总长度，单位为秒
 备注：在prepareWithVid之后才能够获取时长。
 */
@property (nonatomic, readonly,assign)NSTimeInterval duration;

/*
 功能：当前视频播放位置，单位为秒
 备注：在开始播放之后才能够获取当前播放位置。
 */
@property (nonatomic, readonly,assign)NSTimeInterval currentTime;

/*
 功能：获取已经加载的视频长度，或者说对于网络视频来说已经下载的视频时长
 备注：在开始播放之后才能够获取此位置。
 */
@property (nonatomic, readonly,assign)NSTimeInterval loadedTime;

/**
 * 功能：获取视频宽度，只读属性。
 * 备注：当调用了prepareToPlay后，并不能立即获得playVideoWidth的值，只有当播放器发送了prepared通知后，videoWidth的值才有效，否则为默认值0。
 */
@property (nonatomic, readonly,assign)int videoWidth;

/**
 * 功能：获取视频高度，只读属性。
 * 备注：当调用了prepareToPlay后，并不能立即获得playVideoHeight的值，只有当播放器发送了prepared通知后，videoHeight的值才有效，否则为默认值0。
 */
@property (nonatomic, readonly,assign)int videoHeight;

/**
 * 功能：设置/获取清晰度，用来切换视频清晰度
 * 播放器的清晰度有: AliyunVodPlayerVideoFD,            // 流畅
 AliyunVodPlayerVideoLD,            // 标清
 AliyunVodPlayerVideoSD,            // 高清
 AliyunVodPlayerVideoHD,            // 超清
 AliyunVodPlayerVideo2K,            // 2K
 AliyunVodPlayerVideo4K,            // 4K
 AliyunVodPlayerVideoOD,            // 原始
 
 * 备注：在播放之后才能调用
 */
@property (nonatomic, assign) AliyunVodPlayerVideoQuality quality;

/**
 * 功能：设置/获取清晰度，用来切换视频清晰度
 * 备注：在播放之后才能调用
 */
@property (nonatomic, assign) NSString* videoDefinition;

/**
 * 功能：设置倍数播放值
 * 备注：范围0～2：0.5倍(慢速播放)、1倍(正常播放)、1.5倍(加速播放)、2倍(加速播放)
 */
@property(nonatomic, readwrite)  float playSpeed;

/**
 * 功能：日志开关, default : NO
 */
@property (nonatomic, getter=isPrintLog,assign) BOOL printLog;

/**
 * 功能：亮度,调用brightness系统属性，brightness(0~1.0)
 */
@property (nonatomic, readwrite)  float brightness;

/**
 * 功能：声音调节,调用系统MPVolumeView类实现，并非视频声音;volume(0~1.0)
 */
@property (nonatomic, assign) float volume;

/**
 * 功能：获取缓冲的时长，只读属性，单位为毫秒。
 * 备注：当调用了prepareToPlay后，并且开始播放后，才能获取该值。
 */
@property(nonatomic, readonly)  NSTimeInterval bufferPercentage;

/**
 * 功能：循环播放控制
 */
@property(nonatomic, readwrite)  BOOL circlePlay;

/**
 * 功能：
 * 参数：block:音频数据回调
 *
 */
-(void) getAudioData:(void (^)(NSData *data))block;

/**
 * 功能：截取当前正在播放图像
 *
 */
-(UIImage*) snapshot;

/*
 功能：获取此播放器版本号 vision:3.0.0
 */
- (NSString*) getSDKVersion;

/**
 * 功能：当直播时，缓冲区数据大于dropBufferDuration时开始丢数据，单位毫秒，默认8000毫秒
 * 备注：必须大于一个GOP的长度。
 */
@property(nonatomic, readwrite) int dropBufferDuration;



/*
 *直播接口
 */
//直播时间
@property (nonatomic, assign) NSTimeInterval liveTime;
//播放时间
@property (nonatomic, assign) NSTimeInterval currentPlayTime;
//每60秒更新用户时移时间
@property (nonatomic, strong) AliyunPlayerVideoTimeShiftModel *timeShiftModel;

- (void)prepareWithLiveTimeUrl:(NSURL *)liveTimeUrl;

- (void)setLiveTimeShiftUrl:(NSString*)liveTimeShiftUrl;

- (void)seekToLiveTime:(NSTimeInterval)startTime;


@end

