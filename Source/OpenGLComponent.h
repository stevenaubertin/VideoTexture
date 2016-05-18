//
//  OpenGLComponent.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-08.
//
//

#ifndef OpenGLComponent_h
#define OpenGLComponent_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "OpenGL/OpenGLMasterIncludes.h"
#include "Image/ImageHelper.h"
#include "File/PictureFileDialog.h"
#include "Util/Random.h"
#include "MarkerDetection/TopologicalMarkerDetection.h"
#include "Algo/FloodFill.h"

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */
template<class TEXTURE_TYPE=TextureBase>
class OpenGLComponent   : public OpenGLAppComponent{
    ScopedPointer<Shader> shader_;
    ScopedPointer<Shape> shape_;
    ScopedPointer<TextureManager> texture_;
    TEXTURE_TYPE* t_;
    ShaderPreset currentPreset_;
public:
    //==============================================================================
    OpenGLComponent(int width, int height, TEXTURE_TYPE* texture)
        : t_{texture}{
            setSize(width, height);
            
            //This is just because we want to start the random number generator...
            auto v = random_int(0,666);
            v = ++v;
    }
    ~OpenGLComponent(){
        shutdownOpenGL();
    }
    void initialise() override{
        
    }
    void shutdown() override{
        freeAllContextObjects();
    }
private:
    void newOpenGLContextCreated() override{
        freeAllContextObjects();
        
        createShaders();
        texture_ = createTextureManager(openGLContext, t_);
        //shape_ = ShapeFactory::create(File{"/Users/xor/repo/JUCE/examples/OpenGLAppExample copy/Source/Resources/box.obj"},openGLContext);
        shape_ = new TeapotShape (openGLContext);
        
        /*WHATAVER*/
    }
    void openGLContextClosing() override{
        freeAllContextObjects();
    }
    void freeAllContextObjects(){
        shape_ = nullptr;
        texture_ = nullptr;
        shader_ = nullptr;
    }
public:
    void render() override{
        jassert (OpenGLHelpers::isContextActive());
        
        const float desktopScale = static_cast<float>(openGLContext.getRenderingScale());
        OpenGLHelpers::clear (Colour::greyLevel (0.5f));
        
        glEnable (GL_DEPTH_TEST);
        glDepthFunc (GL_LESS);
        glEnable (GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        texture_->activeTexture();
        texture_->update();
        
        glViewport (0, 0, roundToInt (desktopScale * getWidth()), roundToInt (desktopScale * getHeight()));
        
        texture_->bind();
        
        const auto& projMatrix = shape_->getProjectionMatrix(getLocalBounds()).mat;
        const auto& viewMatrix = shape_->getViewMatrix(getFrameCounter()).mat;
        
        shader_->use();
        shader_->getProjectionMatrix().setMatrix4(projMatrix, 1, false);
        shader_->getViewMatrix().setMatrix4(viewMatrix, 1, false);
        shader_->setTexture();
        shader_->setLightPosition(-15.0f, 10.0f, 15.0f, 0.0f);
        
        shape_->draw(openGLContext, shader_->getAttributes());
        
        // Reset the element buffers so child Components draw correctly
        openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, 0);
        openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    void paint (Graphics& g) override{
        // You can add your component specific drawing code here!
        // This will draw over the top of the openGL background.
        
        g.setColour(Colours::white);
        g.setFont (20);
        g.drawText (currentPreset_.getName(), 25, 20, 300, 30, Justification::left);
        g.drawLine (20, 20, 170, 20);
        g.drawLine (20, 50, 170, 50);
    }
    void resized() override{
        // This is called when the MainContentComponent is resized.
        // If you add any child components, this is where you should
        // update their positions.
    }
private:
    void createShaders(){
        static Array<ShaderPreset> presets(getPresets());
        shader_ = ShaderFactory::create(openGLContext, currentPreset_ = presets[2]);
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenGLComponent)
};

#endif /* OpenGLComponent_h */
