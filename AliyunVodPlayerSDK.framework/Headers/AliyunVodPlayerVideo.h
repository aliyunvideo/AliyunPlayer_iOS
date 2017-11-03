//
//  AliyunVodPlayerVideo.h
//  AliyunVodPlayerSDK
//
//  Created by SMY on 16/7/6.
//  Copyright © 2016年 SMY. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AliyunVodPlayerDefine.h"

/*
 AliyunVodPlayerVideo为播放视频信息，prepareDone时候返回该类信息
 */
@interface AliyunVodPlayerVideo : NSObject

/*
 videoId为视频ID
 */
@property (nonatomic, strong) NSString *videoId;

/*
 title为视频显示的标题
 */
@property (nonatomic, strong) NSString *title;

/*
 duration为视频总时长，单位为秒
 */
@property (nonatomic, assign) double duration;

/*
 coverUrl为视频封面
 */
@property (nonatomic,copy)NSString *coverUrl;

/*
 videoQuality为视频清晰度
 */
@property (nonatomic, assign)AliyunVodPlayerVideoQuality videoQuality;

/*
 所有清晰度
 */
@property (nonatomic ,strong)NSArray *allSupportQualitys;

@end



@interface ALPlayerVideoErrorModel : NSObject
//出错的错误信息
@property (nonatomic ,copy)NSString *errorMsg;
//出错的错误码
@property (nonatomic ,assign)int errorCode;
//出错的vid
@property (nonatomic ,copy)NSString *errorVid;
//出错的url
@property (nonatomic ,copy)NSString *errorUrl;
//出错的requestId
@property (nonatomic , copy)NSString *errorRequestId;

@end









