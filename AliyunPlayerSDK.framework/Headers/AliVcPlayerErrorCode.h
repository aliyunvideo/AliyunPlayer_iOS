
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

/**
 *  播放器错误代码
 */

enum{
    ALIVC_SUCCESS                                   = 0,        //无错误
    ALIVC_ERR_INVALID_PARAM                         = 4001 ,    //参数非法，请检查输入参数
    ALIVC_ERR_AUTH_EXPIRED                          = 4002,     //鉴权过期，请重新获取新的鉴权信息
    ALIVC_ERR_INVALID_INPUTFILE                     = 4003,     //无效的输入文件，请检查视频源和路径
    ALIVC_ERR_NO_INPUTFILE                          = 4004,     //没有设置视频源或视频地址不存在
    ALIVC_ERR_READ_DATA_FAILED                      = 4005,     //读取视频源失败
    ALIVC_ERR_LOADING_TIMEOUT                       = 4008,     //视频加载超时，请检查网络状况
    ALIVC_ERR_REQUEST_DATA_ERROR                    = 4009,     //请求数据错误
    ALIVC_ERR_VIDEO_FORMAT_UNSUPORTED               = 4011,     //视频格式不支持
    ALIVC_ERR_PLAYAUTH_PARSE_FAILED                 = 4012,     //playAuth解析失败
    ALIVC_ERR_DECODE_FAILED                         = 4013,     //视频解码失败
    ALIVC_ERR_NO_SUPPORT_CODEC                      = 4019,     //视频编码格式不支持
    ALIVC_ERR_UNKNOWN                               = 4400,     //未知错误
    ALIVC_ERR_REQUEST_ERROR                         = 4500,     //服务端请求错误
    ALIVC_ERR_DATA_ERROR                            = 4501,     //服务器返回数据错误
    ALIVC_ERR_QEQUEST_SAAS_SERVER_ERROR             = 4502,     //请求saas服务器错误
    ALIVC_ERR_QEQUEST_MTS_SERVER_ERROR              = 4503,     //请求mts服务器错误
    ALIVC_ERR_SERVER_INVALID_PARAM                 = 4504,      //服务器返回参数无效，请检查XX参数
    ALIVC_ERR_ILLEGALSTATUS                         = 4521,     //非法的播放器状态，当前状态是xx
    ALIVC_ERR_NO_VIEW                               = 4022,     //没有设置显示窗口，请先设置播放视图
    ALIVC_ERR_NO_MEMORY                             = 4023,     //内存不足
    
    ALIVC_ERR_FUNCTION_DENIED                       = 4024,     //系统权限被拒绝或没有经过授权
    ALIVC_ERR_DOWNLOAD_NO_NETWORK                   = 4101,     //视频下载时连接不到服务器
    ALIVC_ERR_DOWNLOAD_NETWORK_TIMEOUT              = 4102,     //视频下载时网络超时
    ALIVC_ERR_DOWNLOAD_QEQUEST_SAAS_SERVER_ERROR    = 4103,     //请求saas服务器错误
    ALIVC_ERR_DOWNLOAD_QEQUEST_MTS_SERVER_ERROR     = 4104,     //请求mts服务器错误
    ALIVC_ERR_DOWNLOAD_SERVER_INVALID_PARAM         = 4105,     //服务器返回参数无效，请检查XX参数
    ALIVC_ERR_DOWNLOAD_INVALID_INPUTFILE            = 4106,     //视频下载流无效或地址过期
    ALIVC_ERR_DOWNLOAD_NO_ENCRYPT_FILE              = 4107,     //未找到加密文件，请从控制台下载加密文件并集成
    ALIVC_ERR_DONWNLOAD_GET_KEY                     = 4108,     //获取秘钥失败，请检查秘钥文件
    ALIVC_ERR_DOWNLOAD_INVALID_URL                  = 4109,     //下载地址无效
    ALIVC_ERR_DONWLOAD_NO_SPACE                     = 4110,     //磁盘空间不够
    ALIVC_ERR_DOWNLOAD_INVALID_SAVE_PATH            = 4111,     //视频文件保存路径不存在，请重新设置
    ALIVC_ERR_DOWNLOAD_NO_PERMISSION                = 4112,     //当前视频不可下载
    ALIVC_ERR_DOWNLOAD_MODE_CHANGED                 = 4113,     //下载模式改变无法继续下载
    ALIVC_ERR_DOWNLOAD_ALREADY_ADDED                = 4114,     //当前视频已经添加到下载项，请避免重复添加
    ALIVC_ERR_DOWNLOAD_NO_MATCH                     = 4115,     //未找到合适的下载项，请先添加
};

typedef NSInteger AliVcMovieErrorCode;
typedef NSInteger ALPlayerErrorCode;
typedef NSInteger ALPlayerDownLoadErrorCode;

