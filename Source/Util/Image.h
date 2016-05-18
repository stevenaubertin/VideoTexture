//
//  Image.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef Image_h
#define Image_h

#include "../../JuceLibraryCode/JuceHeader.h"

template<class PXL>
static constexpr float getBrightness(const PXL& pxl)noexcept{
    return 0.3f  * pxl.getFloatRed() * 255.0f+
           0.59f * pxl.getFloatGreen() * 255.0f+
           0.11f * pxl.getFloatBlue() * 255.0f;
}

static float getBrightness(const Image& img, int x, int y)noexcept{
    return getBrightness(img.getPixelAt(x,y));
}

#endif /* Image_h */
