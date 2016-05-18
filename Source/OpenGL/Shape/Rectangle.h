//
//  Rectangle.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-09.
//
//

#ifndef Rectangle_h
#define Rectangle_h

#include "Shape.h"

class Rectangle : public Shape{
    Array<Vertex> vertices;
    GLuint vertexBuffer, indexBuffer;
    int numIndices;
public:
    Rectangle(OpenGLContext& openGLContext){
        openGLContext.extensions.glGenBuffers (1, &vertexBuffer);
        openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
    }
    void draw (OpenGLContext& openGLContext, Attributes& glAttributes) override{
        openGLContext.extensions.glBindBuffer (GL_ARRAY_BUFFER, vertexBuffer);
        openGLContext.extensions.glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
        
        glAttributes.enable (openGLContext);
        glDrawElements (GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
        glAttributes.disable (openGLContext);
    }
};

#endif /* Rectangle_h */
