//
//  ImageHelper.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef ImageHelper_h
#define ImageHelper_h

#include "../../JuceLibraryCode/JuceHeader.h"

struct ImageHelper{
    static Image resizeImageToPowerOfTwo (Image image){
        if (! (isPowerOfTwo (image.getWidth()) && isPowerOfTwo (image.getHeight())))
            return image.rescaled (jmin (1024, nextPowerOfTwo (image.getWidth())),
                                   jmin (1024, nextPowerOfTwo (image.getHeight())));
        
        return image;
    }
};

#endif /* ImageHelper_h */
