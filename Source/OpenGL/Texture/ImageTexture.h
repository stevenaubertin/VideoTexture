//
//  ImageTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef ImageTexture_h
#define ImageTexture_h

#include "TextureBase.h"
#include "../../Image/ImageHelper.h"
#include "../../Util/Math.h"

struct ImageTexture : public virtual TextureBase{
    using texture_tag = static_image_texture_tag;
    
    Image image;    
    
    ImageTexture (const Image& img, const String& textureName = String::empty)
        : TextureBase{textureName.isEmpty() ? "Image texture" : textureName},
        image{ImageHelper::resizeImageToPowerOfTwo(img.rescaled(128, 128))}{
    }
    ImageTexture (Image&& img, const String& textureName = String::empty)
        : TextureBase{textureName.isEmpty() ? "Image texture" : textureName}, image{std::move(img)}{
    }
    ImageTexture (const void* imageData, size_t imageSize, const String& textureName = String::empty)
        : TextureBase{textureName.isEmpty() ? "Image texture" : textureName},
          image(ImageHelper::resizeImageToPowerOfTwo (ImageFileFormat::loadFrom (imageData, imageSize))){
    }
    virtual bool applyTo (OpenGLTexture& texture) override{
        //KMeansSegmentation(image);
        texture.loadImage(image);
        return false;
    }
};


#endif /* ImageTexture_h */
