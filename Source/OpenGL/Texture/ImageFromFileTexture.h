//
//  ImageFromFileTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef ImageFromFileTexture_h
#define ImageFromFileTexture_h

#include "ImageTexture.h"

struct ImageFromFileTexture : public virtual ImageTexture{
    ImageFromFileTexture(const File& file, const String& name = String::empty)
        : ImageTexture{ImageHelper::resizeImageToPowerOfTwo(ImageFileFormat::loadFrom(file)),
                       name.isEmpty() ? file.getFileName() : name}{
    }
};

#endif /* ImageFromFileTexture_h */
