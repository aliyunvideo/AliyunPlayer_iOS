#ifndef __MPLAYING_HANDLER_H__
#define __MPLAYING_HANDLER_H__

typedef bool (*audioDataCallback)(char* pcmData,int dataSize,void* userData);

//Function return error-code.
typedef enum _mp_status_t{
    E_MP_UNKNOW = -1,

    E_MP_OK,                //successfully
    E_MP_NONE,              //nothing could be play. empty file.
    E_MP_FAILED,           //failed
    E_MP_UNSUPPORT,        //Unsupport
    E_MP_INVALID_OPERATE,  //function invoke order wrong probably

    E_MP_OUTOFMEM,   //out of memory
    E_MP_INVALID_ARGS //invalid argumets
} mp_status_t;

class IMPlayerHandler{
public:
    virtual ~IMPlayerHandler(){};
public:
    
    //define what status
    enum {
        MSG_OPEN_STATUS = 0
        , MSG_LOAD_STATUS
        , MSG_PLAY_STATUS
        , MSG_PREPARE_STATUS
        , MSG_PLAY_PROGRESS       //set the update-progress, arg0 is the progress, arg1 means it is audio or video

        , MSG_DECODE_STATUS
        , MSG_SIZE_STATUS
        , MSG_INFO_REPORT
        , MSG_FIRST_FRAME
        , MSG_PCM_DATA

        , MSG_CAPTURE_FRAME_DATA
    };
    
    //info report type
    enum {
        INFOREPORT_EMPTY = 0
        ,INFOREPORT_OPEN_PLAY
        ,INFOREPORT_SEEK_START
        ,INFOREPORT_SEEK_END
        ,INFOREPORT_PAUSE_START

        ,INFOREPORT_PAUSE_END
        ,INFOREPORT_STOP
        ,INFOREPORT_BUFFERING_START
        ,INFOREPORT_BUFFERING_END
        ,INFOREPORT_EOS

        ,INFOREPORT_PLAYING_DOWN
    };
    
    //define arg0 now.
    enum {
        
        k0Unknown = -1

        , k0None = 0
        , k0PrepareStart
        , k0PrepareFailed
        , k0Prepared         //arg1 is total - duration  //csp:OriginOnPreparedListener
        , k0OpenStart

        , k0OpenFailed
        , k0Opened
        , k0LoadStart       //
        , k0LoadFailed
        , k0Loading        //arg1 is the loading time in ms.

        , k0Loaded         //arg1 is the loading time pts in ms.
        , k0PlayStarted
        , k0PlayPaused
        , k0PlayPausedForBuffering
        , k0PlayPausedForBufferingDone

        , k0PlayResumed
        , k0PlayStopped
        , k0PlaySeekDone // when seek handle get done and video played. arg0 is the progress value in ms.  //csp:OriginSeekCompleteListener
        , k0PlayEnd   //csp:OriginOnCompleteListener
        , k0DecodeDone  //decode done. arg1 indeicate if it is audio or video

        , k0LoadingStart
        , k0LoadingEnd
        , k0LoadingProgress // arg1 is the progress
        , k0LoadingTimeout
        , k0AudioDecoding

        , k0CircleStart
        
    };
    
    //define arg1
    enum{
        k1Unknow = -1,//csp:OriginOnErrorListener

        k1None = 0,
        k1NetworkError,//csp:OriginOnErrorListener
        k1FileOpenError,//csp:OriginOnErrorListener
        k1FileDemuxError,//csp:OriginOnErrorListener
        k1InvalidFile,//csp:OriginOnErrorListener

        k1AudioPlayed,
        k1VideoPlayed,
        k1NoInputFile,
        k1NoMemory,
        k1NoSupportCodec,

        k1NoVideo,
        k1NetworkTimeout,
        k1InvalidPswd,
        k1AudioDecodeFail,
    };
    
    //==
    virtual bool onStatus(int what, int arg0, int arg1, void* custom_data) = 0;
    
public:
    int   mPlayerId;
};



#endif // __MPLAYING_HANDLER_H__

