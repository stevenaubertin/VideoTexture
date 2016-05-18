//
//  ImageFromCameraComponent.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-09.
//
//

#ifndef ImageFromCameraComponent_h
#define ImageFromCameraComponent_h

#include "CameraManager.h"

#include "../Util/Math.h"

class ImageFromCameraComponent: private CameraDevice::Listener,
                                private AsyncUpdater{
    CameraManager& cameraManager_;
    ImageComponent* comp_;
    Image image_;
public:
    ImageFromCameraComponent(CameraManager& cameraManager, ImageComponent* comp)noexcept
        : cameraManager_{cameraManager}, comp_{comp}{
    }
    ~ImageFromCameraComponent(){
        toggleImageFrames(false);
        if(comp_!=nullptr){
            comp_->setImage(Image::null);
        }
    }
    void toggleImageFrames(bool toggle){
        if(toggle){
            cameraManager_.addListener(this);
        }
        else{
            cameraManager_.removeListener(this);
        }
    }
private:
    void imageReceived (const Image& image) override{
        static int count = 0;
        image_ = image;
        if(++count % 5 == 0)KMeansSegmentation(image_);
        triggerAsyncUpdate();
    }
    virtual void handleAsyncUpdate() override{
        if (image_.isValid()){
            comp_->setImage(image_);
        }
    }
};


#endif /* ImageFromCameraComponent_h */
