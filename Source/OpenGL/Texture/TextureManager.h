//
//  TextureManager.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef TextureManager_h
#define TextureManager_h

#include <type_traits>
#include <atomic>

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "TextureBase.h"



struct TextureManager{
protected:
    OpenGLContext& context_;
    ScopedPointer<TextureBase> t_;
    OpenGLTexture texture_;
    std::atomic<bool> wasRelease_;
public:
    TextureManager(OpenGLContext& context, ScopedPointer<TextureBase> t)
        : context_{context}, t_{t}, wasRelease_{false}{
        update();
    }
    virtual ~TextureManager(){
        bool b;
        if(wasRelease_.compare_exchange_weak(b, true)){
            texture_.release();
        }
    }
    virtual void activeTexture() noexcept{
        context_.extensions.glActiveTexture (GL_TEXTURE0);
        glEnable (GL_TEXTURE_2D);
    }
    bool update(){
        return t_->applyTo(texture_);
    }
    void bind()const noexcept{
        texture_.bind();
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
};

struct StaticTextureManager : public TextureManager{
    StaticTextureManager(OpenGLContext& context, ScopedPointer<TextureBase> t)
        : TextureManager{context, t}{
    }
};
struct DynamicTextureManager : public TextureManager{
    DynamicTextureManager(OpenGLContext& context, ScopedPointer<TextureBase> t)
        : TextureManager{context, t}{
    }
    void activeTexture() noexcept override{
        context_.extensions.glActiveTexture (GL_TEXTURE0);
        glEnable (GL_TEXTURE_2D);
        update();
    }
};

TextureManager* createTextureManager_impl(OpenGLContext& context, ScopedPointer<TextureBase> t, dynamic_texture_tag){
    return new DynamicTextureManager{context, t};
}
TextureManager* createTextureManager_impl(OpenGLContext& context, ScopedPointer<TextureBase> t, static_texture_tag){
    return new StaticTextureManager{context, t};
}
template<class TEXT_T>
TextureManager* createTextureManager(OpenGLContext& context, TEXT_T* texture){
    return createTextureManager_impl(context, texture, typename texture_traits<TEXT_T>::texture_tag{});
}

#endif /* TextureManager_h */








