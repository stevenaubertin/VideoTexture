//
//  JuceLogoTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef JuceLogoTexture_h
#define JuceLogoTexture_h

#include "ImageTexture.h"

struct JuceLogoTexture : public ImageTexture{
    JuceLogoTexture()
        : ImageTexture{BinaryData::juce_icon_png, BinaryData::juce_icon_pngSize, "JUCE logo"}{
    }
};

#endif /* JuceLogoTexture_h */
