//
//  BinaryShape.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef BinaryShape_h
#define BinaryShape_h

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../Object/WavefrontObjParser.h"

class BinaryShape : public Shape{
    WavefrontObjFile shapeFile;
    class VertexBuffer;
    OwnedArray<VertexBuffer> vertexBuffers;
public:
    BinaryShape (OpenGLContext& openGLContext, const char* binObj){
        if (shapeFile.load(binObj).wasOk()){
            for (int i = 0; i < shapeFile.shapes.size(); ++i){
                vertexBuffers.add (new VertexBuffer (openGLContext, *shapeFile.shapes.getUnchecked(i)));
            }
        }
    }
    void draw (OpenGLContext& openGLContext, Attributes& glAttributes) override{
        for (int i = 0; i < vertexBuffers.size(); ++i){
            VertexBuffer& vertexBuffer = *vertexBuffers.getUnchecked (i);
            vertexBuffer.bind();
            
            glAttributes.enable (openGLContext);
            glDrawElements (GL_TRIANGLES, vertexBuffer.numIndices, GL_UNSIGNED_INT, 0);
            glAttributes.disable (openGLContext);
        }
    }
private:
    struct VertexBuffer{
        GLuint vertexBuffer, indexBuffer;
        int numIndices;
        OpenGLContext& openGLContext;
        
        VertexBuffer (OpenGLContext& context, WavefrontObjFile::Shape& aShape)
        : openGLContext (context){
            numIndices = aShape.mesh.indices.size();
            
            openGLContext.extensions.glGenBuffers (1, &vertexBuffer);
            openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
            
            Array<Vertex> vertices;
            createVertexListFromMesh (aShape.mesh, vertices, Colours::green);
            
            openGLContext.extensions.glBufferData (GL_ARRAY_BUFFER,
                                                   static_cast<GLsizeiptr> (static_cast<size_t> (vertices.size()) * sizeof (Vertex)),
                                                   vertices.getRawDataPointer(), GL_STATIC_DRAW);
            
            openGLContext.extensions.glGenBuffers (1, &indexBuffer);
            openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
            openGLContext.extensions.glBufferData (GL_ELEMENT_ARRAY_BUFFER,
                                                   static_cast<GLsizeiptr> (static_cast<size_t> (numIndices) * sizeof (juce::uint32)),
                                                   aShape.mesh.indices.getRawDataPointer(), GL_STATIC_DRAW);
        }
        ~VertexBuffer(){
            openGLContext.extensions.glDeleteBuffers (1, &vertexBuffer);
            openGLContext.extensions.glDeleteBuffers (1, &indexBuffer);
        }
        void bind(){
            openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
            openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        }
        
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VertexBuffer)
    };
};

#endif /* BinaryShape_h */
