//
//  PortmeirionTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef PortmeirionTexture_h
#define PortmeirionTexture_h

#include "ImageTexture.h"

struct PortmeirionTexture : public ImageTexture{
    PortmeirionTexture()
        : ImageTexture{BinaryData::portmeirion_jpg, BinaryData::portmeirion_jpgSize, "Portmeirion"}{
    }
};

#endif /* PortmeirionTexture_h */
