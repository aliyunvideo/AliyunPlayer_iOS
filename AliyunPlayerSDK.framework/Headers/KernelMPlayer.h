 #ifndef __KERNEL_MPLAYER_H__
#define __KERNEL_MPLAYER_H__

#include "MPlayingHandler.h"

//class kernelMPlayer
class kernelMPlayer
{
public:
    kernelMPlayer(void *eagl_view, IMPlayerHandler* handler);
    ~kernelMPlayer();

#ifdef __ANDROID__
    int setVideoSurface(void *nativeWindow);
    int releaseVideoSurface();
#endif

#ifdef __ANDROID__
    mp_status_t prepare(const char* url, int start_ms, int& decoder_type,const char* videoKey,int circleCount=10); //in ms.
#else
    mp_status_t prepare(const char* url, int start_ms,const char* videoKey=NULL,int circleCount=10); //in ms.
#endif

    void setSurfaceChanged();

    //return ms
    int get_total_duration();

    //return ms
    int get_current_position();
    
    //return ms
    int get_buffering_position();

    //return the video size: w and h. invoked after prepare.
    mp_status_t get_video_size(int& w, int& h);

    //set the buffering max time length.
    // before invoking start(). by default it is 100 sec.
    void setBufferingTimeLength(int max_ms);

    bool  isPlaying();
    
    bool  isPaused();

    //you need invoke prepare() before invoking the following functions.
    mp_status_t start();
    mp_status_t stop();
    mp_status_t pause();

    //pause for buffering...
    mp_status_t pause_for_buffering(int buffering_time_ms);

    mp_status_t resume();
    mp_status_t seekTo(int ms);
    
    bool notify(int what, int arg0, int arg1, void *custom_data);
    
    void setMuteMode(bool bmute);
    
    void setAudioDataCallback(audioDataCallback callback,void* userData);
    
    void setCirclePlay(bool bCirclePlay);
private:
    void* m_player;
};



#endif // __KERNEL_MPLAYER_H__

