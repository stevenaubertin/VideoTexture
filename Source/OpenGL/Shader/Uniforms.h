//
//  Uniforms.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef Uniforms_h
#define Uniforms_h

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
// This class just manages the uniform values that the demo shaders use.
struct Uniforms{
    ScopedPointer<OpenGLShaderProgram::Uniform> projectionMatrix;
    ScopedPointer<OpenGLShaderProgram::Uniform> viewMatrix;
    ScopedPointer<OpenGLShaderProgram::Uniform> texture;
    ScopedPointer<OpenGLShaderProgram::Uniform> lightPosition;
    
    Uniforms (OpenGLContext& openGLContext, OpenGLShaderProgram& shader){
        projectionMatrix = createUniform (openGLContext, shader, "projectionMatrix");
        viewMatrix       = createUniform (openGLContext, shader, "viewMatrix");
        texture          = createUniform (openGLContext, shader, "demoTexture");
        lightPosition    = createUniform (openGLContext, shader, "lightPosition");
    }
    
private:
    static OpenGLShaderProgram::Uniform* createUniform (OpenGLContext& openGLContext,
                                                        OpenGLShaderProgram& shaderProgram,
                                                        const char* uniformName){
        if (openGLContext.extensions.glGetUniformLocation (shaderProgram.getProgramID(), uniformName) < 0)
            return nullptr;
        
        return new OpenGLShaderProgram::Uniform (shaderProgram, uniformName);
    }
};

#endif /* Uniforms_h */
