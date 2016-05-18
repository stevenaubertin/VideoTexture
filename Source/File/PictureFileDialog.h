//
//  PictureFileDialog.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef PictureFileDialog_h
#define PictureFileDialog_h

#include "OpenFileDialog.h"

class PictureFileDialog : public OpenFileDialog{
public:
    PictureFileDialog()
        : OpenFileDialog(File::getSpecialLocation(File::userPicturesDirectory),
                         "*.jpg;*.jpeg;*.png;*.gif"){
    }
};


#endif /* PictureFileDialog_h */
