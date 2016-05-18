//
//  TeapotShape.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef TeapotShape_h
#define TeapotShape_h

#include "BinaryShape.h"

struct TeapotShape : public BinaryShape{
    TeapotShape(OpenGLContext& openGLContext)
        : BinaryShape{openGLContext, BinaryData::teapot_obj} {
    }
    Matrix3D<float> getProjectionMatrix(const Rectangle<int>& localBounds, float scale) const override{
        const float w = 1.0f / (0.5f + 0.1f);
        const float h = w * localBounds.toFloat().getAspectRatio(false);
        return Matrix3D<float>::fromFrustum(-w, w, -h, h, 4.0f, 30.0f);
    }
    Matrix3D<float> getViewMatrix(int frameCount) const override{
        const Matrix3D<float> viewMatrix(Vector3D<float> (0.0f, 0.0f, -10.0f));
        const Matrix3D<float> rotationMatrix(viewMatrix.rotated(Vector3D<float>(-0.3f, 5.0f * std::sin(frameCount * 0.01f), 0.0f)));
        return rotationMatrix * viewMatrix;
        
        return viewMatrix;
    }
};


#endif /* TeapotShape_h */
