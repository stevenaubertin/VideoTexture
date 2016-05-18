//
//  VideoTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef VideoTexture_h
#define VideoTexture_h

#include "DynamicTexture.h"
#include "../../../JuceLibraryCode/JuceHeader.h"
#include "CameraManager.h"
#include <atomic>

class VideoTexture : public DynamicTexture,
                     private CameraDevice::Listener{
public:
    enum{SIZE = 128};
private:
    static const Image DEFAULT_IMAGE;
    CameraManager& c_;
    Image image_;
    std::atomic<bool> b_;
public:
    using texture_tag = video_texture_tag;
    VideoTexture(CameraManager& c)
        : c_{c}, image_{Image::null}, b_{false}{
            try{c_.open();}
            catch(CameraAlreadyOpenException){}
            c_.addListener(this);
            b_ = true;
    }
    ~VideoTexture(){
        bool b;
        if(b_.compare_exchange_weak(b, false)){
            c_.removeListener(this);
            image_ = Image::null;
        }
    }
    bool applyTo (OpenGLTexture& texture) override{
        image_ = image_.isValid() ? image_.rescaled(SIZE, SIZE) : DEFAULT_IMAGE;
        texture.loadImage(image_);
        return false;
    }
private:
    void imageReceived (const Image& image) override{
        image_ = image;
    }
};

#endif /* VideoTexture_h */
