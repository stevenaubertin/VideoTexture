//
//  CameraManager.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-08.
//
//

#ifndef CameraManager_h
#define CameraManager_h

#include "../../JuceLibraryCode/JuceHeader.h"
#include <vector>

class NoCameraAvailableException{};
class CameraAlreadyOpenException{};
class CameraNotOpenException{};
class ImageComponentNullException{};

class CameraManager{
    ScopedPointer<CameraDevice> cameraDevice_;
public:
    StringArray getAvailableDevices()const noexcept{
        return CameraDevice::getAvailableDevices();
    }
    void open(){
        if(cameraDevice_!=nullptr){
            throw CameraAlreadyOpenException{};
        }
        const auto availablesDevices = getAvailableDevices();
        if(availablesDevices.isEmpty()){
            throw NoCameraAvailableException{};
        }
        cameraDevice_ = CameraDevice::openDevice(0);
    }
    Component* getCameraPreviewComponent(){
        if(cameraDevice_==nullptr){
            throw CameraNotOpenException{};
        }
        return cameraDevice_->createViewerComponent();
    }
    void addListener(CameraDevice::Listener* l){
        if(cameraDevice_==nullptr){
            throw CameraNotOpenException{};
        }
        cameraDevice_->addListener(l);
    }
    void removeListener(CameraDevice::Listener* l){
        if(cameraDevice_!=nullptr){
            cameraDevice_->removeListener(l);
        }
    }
};


#endif /* CameraManager_h */
