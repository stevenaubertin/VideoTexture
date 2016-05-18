//
//  Attributes.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef Attributes_h
#define Attributes_h

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
// This class just manages the attributes that the shaders use.
struct Attributes{
    Attributes (OpenGLContext& openGLContext, OpenGLShaderProgram& shaderProgram)
    {
        position      = createAttribute (openGLContext, shaderProgram, "position");
        normal        = createAttribute (openGLContext, shaderProgram, "normal");
        sourceColour  = createAttribute (openGLContext, shaderProgram, "sourceColour");
        texureCoordIn = createAttribute (openGLContext, shaderProgram, "texureCoordIn");
    }
    
    void enable (OpenGLContext& openGLContext)
    {
        if (position != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (position->attributeID, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), 0);
            openGLContext.extensions.glEnableVertexAttribArray (position->attributeID);
        }
        
        if (normal != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (normal->attributeID, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 3));
            openGLContext.extensions.glEnableVertexAttribArray (normal->attributeID);
        }
        
        if (sourceColour != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (sourceColour->attributeID, 4, GL_FLOAT, GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 6));
            openGLContext.extensions.glEnableVertexAttribArray (sourceColour->attributeID);
        }
        
        if (texureCoordIn != nullptr)
        {
            openGLContext.extensions.glVertexAttribPointer (texureCoordIn->attributeID, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (GLvoid*) (sizeof (float) * 10));
            openGLContext.extensions.glEnableVertexAttribArray (texureCoordIn->attributeID);
        }
    }
    
    void disable (OpenGLContext& openGLContext)
    {
        if (position != nullptr)       openGLContext.extensions.glDisableVertexAttribArray (position->attributeID);
        if (normal != nullptr)         openGLContext.extensions.glDisableVertexAttribArray (normal->attributeID);
        if (sourceColour != nullptr)   openGLContext.extensions.glDisableVertexAttribArray (sourceColour->attributeID);
        if (texureCoordIn != nullptr)  openGLContext.extensions.glDisableVertexAttribArray (texureCoordIn->attributeID);
    }
    
    ScopedPointer<OpenGLShaderProgram::Attribute> position, normal, sourceColour, texureCoordIn;
    
private:
    static OpenGLShaderProgram::Attribute* createAttribute (OpenGLContext& openGLContext,
                                                            OpenGLShaderProgram& shader,
                                                            const char* attributeName)
    {
        if (openGLContext.extensions.glGetAttribLocation (shader.getProgramID(), attributeName) < 0)
            return nullptr;
        
        return new OpenGLShaderProgram::Attribute (shader, attributeName);
    }
};

#endif /* Attributes_h */
