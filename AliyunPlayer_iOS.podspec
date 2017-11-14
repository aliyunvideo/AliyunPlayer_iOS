Pod::Spec.new do |s|
  s.name         = "AliyunPlayer_iOS"
  s.version      = "1.0.7"
  s.summary      = "AliyunPlayer_iOS."
  s.description  = <<-DESC
                   It's an SDK for aliyun video vodplay, which implement by Objective-C.
                   DESC
  s.homepage     = "https://github.com/aliyunvideo/AliyunPlayer_iOS"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.author       = { "aliyunvideo" => "videosdk@service.aliyun.com"}
  s.platform     = :ios
  s.platform     = :ios, "8.0"
  s.source       = { :git => "https://github.com/aliyunvideo/AliyunPlayer_iOS.git", :tag => "#{s.version}" }
	
  s.subspec 'AliyunVodPlayerSDK' do |vodplayer|
	vodplayer.vendored_frameworks = 'AliyunVodPlayerSDK.framework'
	vodplayer.resource = 'AliyunLanguageSource.bundle'
	vodplayer.frameworks = 'VideoToolBox','MediaPlayer'
	vodplayer.libraries = 'z'	
  end	

  #s.subspec 'AliyunVodPlayerViewSDK' do |vodplayerview|
#	vodplayerview.vendored_frameworks = 'AliyunVodPlayerViewSDK.framework'
#	vodplayerview.dependency 'AliyunPlayer_iOS/AliyunVodPlayerSDK'
#	vodplayerview.resource  = 'AliyunLanguageSource.bundle','AliyunImageSource.bundle'
 # end
 
  #s.ios.vendored_frameworks = 'AliyunVodPlayerSDK.framework','AliyunVodPlayerViewSDK.framework'
  #s.resource = 'AliyunVodPlayerViewResource.bundle'
  #s.frameworks = 'VideoToolBox','MediaPlayer'
  #s.libraries = 'z'  
  s.requires_arc = true
   

end
