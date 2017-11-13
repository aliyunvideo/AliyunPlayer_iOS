//
//  AliyunVodeDownLoadManager.h
//  AliyunVodPlayerSDK
//
//  Created by 王凯 on 2017/6/13.
//  Copyright © 2017年 SMY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AliyunVodPlayerDefine.h"

@interface AliyunDownloadMediaInfo : NSObject
@property(nonatomic,copy)NSString *vid;
@property(nonatomic,copy)NSString *title;
@property(nonatomic,copy)NSString *coverURL;
@property(nonatomic,assign)AliyunVodPlayerVideoQuality  quality;
@property(nonatomic,assign)int downloadProgress;
@property(nonatomic,copy)NSString *downloadFilePath;
@property(nonatomic,assign)int64_t duration;
@property(nonatomic,assign)int64_t size;
@property(nonatomic,copy)NSString* format;
@end


@interface AliyunStsData :NSObject
@property(nonatomic,copy)NSString *accessKeyId;
@property(nonatomic,copy)NSString *accessKeySecret;
@property(nonatomic,copy)NSString *securityToken;

@end

@interface AliyunDataSource : NSObject

@property (nonatomic,assign)AliyunVodRequestMethod requestMethod;
@property(nonatomic,copy)NSString *vid;
@property(nonatomic,copy)NSString *playAuth;
@property(nonatomic,assign)AliyunVodPlayerVideoQuality quality;
@property(nonatomic,copy)NSString *format;

@property(nonatomic,strong)AliyunStsData *stsData;

@end




@class AliyunVodDownLoadManager;

@protocol AliyunVodDownLoadDelegate <NSObject>

/*
 功能：未完成回调，异常中断导致下载未完成，下次启动后会接收到此回调。
 回调数据：AliyunDownloadMediaInfo数组
 */
-(void) onUnFinished:(NSArray<AliyunDataSource*>*)mediaInfos;


/*
  功能：开始下载后收到回调，更新最新的playAuth。主要场景是开始多个下载时，等待下载的任务自动开始下载后，playAuth有可能已经过期了，需通过此回调更新
  */
-(NSString*) onGetPlayAuth:(NSString*)vid format:(NSString*)format quality:(AliyunVodPlayerVideoQuality)quality;


/*
  功能：开始下载后收到回调，更新最新的stsData。主要场景是开始多个下载时，等待下载的任务自动开始下载后，stsData有可能已经过期了，需通过此回调更新
 */
- (void)onGetAliyunStsData:(AliyunStsData*)stsData
                   videoID:(NSString *)videoID
                    format:(NSString*)format
                   quality:(AliyunVodPlayerVideoQuality)quality;


/*
 功能：准备下载回调。
 回调数据：AliyunDownloadMediaInfo数组
 */
-(void) onPrepare:(NSArray<AliyunDownloadMediaInfo*>*)mediaInfos;

/*
 功能：下载开始回调。
 回调数据：AliyunDownloadMediaInfo
 */
-(void) onStart:(AliyunDownloadMediaInfo*)mediaInfo;

/*
  功能：下载进度回调。可通过mediaInfo.downloadProgress获取进度。
  回调数据：AliyunDownloadMediaInfo
  */
-(void) onProgress:(AliyunDownloadMediaInfo*)mediaInfo;

/*
  功能：调用stop结束下载时回调。
  回调数据：AliyunDownloadMediaInfo
  */
-(void) onStop:(AliyunDownloadMediaInfo*)mediaInfo;

/*
  功能：下载完成回调。
  回调数据：AliyunDownloadMediaInfo
  */
-(void) onCompletion:(AliyunDownloadMediaInfo*)mediaInfo;

/*
  功能：改变加密文件（调用changeEncryptFile时回调）。
  回调数据：重新加密之前视频文件进度
  */
-(void) onChangeEncryptFileProgress:(int)progress;


/*
  功能：改变加密文件后老的加密视频重新加密完成时回调。加密完成后注意删除老的加密文件。
  */
-(void) onChangeEncryptFileComplete;

/*
  功能：错误回调。错误码与错误信息详见文档。
  回调数据：AliyunDownloadMediaInfo， code：错误码 msg：错误信息
  */
-(void)onError:(AliyunDownloadMediaInfo*)mediaInfo code:(int)code msg:(NSString *)msg;

@end


@interface AliyunVodDownLoadManager : NSObject

@property(nonatomic,weak)id<AliyunVodDownLoadDelegate>downloadDelegate;

          
/*
 功能：获取下载器
 备注：单例
 */
+(AliyunVodDownLoadManager*)shareManager;

/*
 功能：配置下载路径
 参数：dir 下载的目标目录。如果不存在，将自动创建。
 */
-(void)setDownLoadPath:(NSString *)path;

/*
 功能：设置同时下载的数量，最大4个
 参数：count:同时下载的个数
 */
-(void)setMaxDownloadOperationCount:(int)count;

/*
  功能：设置加密文件
  参数：encrptyFile为加密文件路径
  */
-(void)setEncrptyFile:(NSString*)encrptyFile;


/*
  功能：改变加密文件，主要场景是新版本要升级加密文件，对于老版本已经下载的加密视频文件需要重新加密才能播放。
  参数：oldEncrptyFile,老的加密文件
  参数：newEncryptFile,新的加密文件
  参数：mp4Files,需要转换的文件列表
  */
-(int)changeEncryptFile:(NSString*)oldEncrptyFile newEncryptFile:(NSString*)newEncryptFile mp4Files:(NSArray*)mp4Files;

/*
 功能：设置下载进度监听器。
 参数：listener 下载进度监听器。具体见下表。
 */
-(void)downLoadInfoListenerDelegate:(id<AliyunVodDownLoadDelegate>)delegate;

/*
 功能：调用此方法来获取下载媒体信息，OnPrepare回调来获取
 参数：dataSource 视频信息源。
 */
-(void)prepareDownloadMedia:(AliyunDataSource*)dataSource;

/*
 功能：开始下载单个视频资源。调用此方法后，开始下载视频。
 参数：dataSource 视频信息源。
 */
-(void) startDownloadMedia:(AliyunDataSource*)dataSource;

/*
 功能：开始下载视频资源列表。调用此方法后，会依次下载列表中的视频。
 参数：dataSources 视频信息源列表。
 */
-(void) startDownloadMedias:(NSArray<AliyunDataSource*>*)dataSources;

/*
 功能：结束下载视频资源。
 参数：downloadInfo 视频信息项。
 */
-(void) stopDownloadMedia:(AliyunDownloadMediaInfo*)downloadInfo;

/*
 功能：停止所有下载视频资源。
 */
-(void) stopAllDownloadMedia;

/*
 功能：结束下载视频资源列表。
 参数：downloadInfos 视频信息项列表。
 */
-(void) stopDownloadMedias:(NSArray<AliyunDownloadMediaInfo*>*)downloadInfos;

/*
 功能：获取正在下载视频资源列表,包括等待下载列表。
 参数：downloadInfos 视频信息项列表。
 */
-(NSArray<AliyunDownloadMediaInfo*>*) downloadingdMedias;

/*
 功能：获取正在下载视频资源列表。
 参数：downloadInfos 视频信息项列表。
 */
-(NSArray<AliyunDownloadMediaInfo*>*) currentDownloadingdMedias;


/*
 功能：获取所有的视频资源列表，包括停止的，正在下载的。
 参数：downloadInfos 视频信息项列表。
 */
-(NSArray<AliyunDownloadMediaInfo*>*) allMedias;

/*
 功能：清除所有下载的媒体资源。
 */
-(void) clearAllMedias;

/*
 功能：清除指定下载的媒体资源。
 */
-(void) clearMedia:(AliyunDownloadMediaInfo*)downloadInfo;

/*
 功能：获取下载功能的SDK版本号。
 */
- (NSString*) getSDKVersion;

@end
