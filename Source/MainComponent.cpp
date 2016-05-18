/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "OpenGLComponent.h"
#include "File/PictureFileDialog.h"
#include "Camera/CameraManager.h"
#include "Camera/ImageFromCameraComponent.h"

#include "Util/Math.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainContentComponent : public Component{
    ScopedPointer<OpenGLComponent<ImageTexture>> openGlComponent_;
    ScopedPointer<Component> c_;
    CameraManager cameraManager_;
    ScopedPointer<ImageFromCameraComponent> ifc_;
    
public:
    //==============================================================================
    MainContentComponent(){
        setSize (800, 600);
        
        static PictureFileDialog dialog;
        auto r = dialog.openFile();
        assert(r);
        
        addAndMakeVisible(openGlComponent_ = new OpenGLComponent<ImageTexture>{
            this->getWidth(),
            this->getHeight(),
            new ImageTexture{ImageFileFormat::loadFrom(r)}//new DynamicBouncingNumberTexture{}//new VideoTexture{cameraManager_}//
        });
        //openGlComponent_->addAndMakeVisible(c_ = createImageComponent());
        //openGlComponent_->addAndMakeVisible(c_ = createImageComponent(true));//createCameraComponent());
        //addAndMakeVisible(c_ = createImageComponent(true));
    }
    void paint (Graphics& g) override{
    }
    void resized() override{
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
        if(c_ != nullptr)c_->setTopLeftPosition(this->getWidth() - c_->getWidth() - 15, -15);//c_->setSize(this->getWidth(),this->getHeight());
        if(openGlComponent_ != nullptr)openGlComponent_->setSize(this->getWidth(),this->getHeight());
    }
private:
    Component* createCameraComponent(){
        cameraManager_.open();
        Component* c = cameraManager_.getCameraPreviewComponent();
        c->setSize(255,200);
        c->setTopLeftPosition(this->getWidth() - c->getWidth() - 15, -15);
        return c;
    }
    Component* createImageComponent(bool fromCamera=false){
        try{cameraManager_.open();}
        catch(...){}
        ImageComponent* c = new ImageComponent();
        if(fromCamera){
            ifc_ = new ImageFromCameraComponent{cameraManager_, c};
            ifc_->toggleImageFrames(true);
        }
        else{
            static PictureFileDialog dialog;
            auto r = dialog.openFile();
            assert(r);
            c->setImage(ImageFileFormat::loadFrom(r));
        }
        //c->setSize(this->getWidth(),this->getHeight());
        c->setSize(255,200);
        c->setTopLeftPosition(this->getWidth() - c->getWidth() - 15, -15);
        return c;
    }    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


// (This function is called by the app startup code to create our main component)
Component* createMainContentComponent()    { return new MainContentComponent(); }


#endif  // MAINCOMPONENT_H_INCLUDED
