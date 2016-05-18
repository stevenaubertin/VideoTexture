//
//  TiledBackgroundTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef TiledBackgroundTexture_h
#define TiledBackgroundTexture_h

#include "ImageTexture.h"

struct TiledBackgroundTexture : public ImageTexture{
    TiledBackgroundTexture()
        : ImageTexture{BinaryData::tile_background_png, BinaryData::tile_background_pngSize, "Tiled Background"}{
    }
};

#endif /* TiledBackgroundTexture_h */
