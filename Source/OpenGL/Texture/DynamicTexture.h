//
//  DynamicTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef DynamicTexture_h
#define DynamicTexture_h

#include "TextureBase.h"

struct DynamicTexture  : public virtual TextureBase{
    using texture_tag = dynamic_texture_tag;
    
    DynamicTexture(const String& name = String::empty)
        : TextureBase{name.isEmpty() ? "Dynamically-generated texture" : name} {
    }
    virtual ~DynamicTexture(){}
    virtual bool applyTo (OpenGLTexture& texture) override = 0;
};


#endif /* DynamicTexture_h */
