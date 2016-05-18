//
//  Shape.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef Shape_h
#define Shape_h

#include "../../../JuceLibraryCode/JuceHeader.h"

struct Shape{
    virtual ~Shape(){}
    virtual void draw (OpenGLContext& openGLContext, Attributes& glAttributes) = 0;
    virtual Matrix3D<float> getProjectionMatrix(const Rectangle<int>& localBounds, float scale = 0.5f) const{
        const float w = 1.0f / (scale + 0.1f);
        const float h = w * localBounds.toFloat().getAspectRatio(false);
        return Matrix3D<float>::fromFrustum(-w, w, -h, h, 4.0f, 10.0f);
    }
    virtual Matrix3D<float> getViewMatrix(int frameCount) const{
        return {Vector3D<float> (0.0f, 0.0f, -10.0f)};
    }
};

#endif /* Shape_h */
