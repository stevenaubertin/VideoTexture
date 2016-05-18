//
//  ShapeFactory.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-09.
//
//

#ifndef ShapeFactory_h
#define ShapeFactory_h

#include "../JuceLibraryCode/JuceHeader.h"
#include "BinaryShape.h"

struct ShapeFactory{
    static Shape* create(const File& f, OpenGLContext& openGLContext){
        MemoryBlock mem;
        f.loadFileAsData(mem);
        return new BinaryShape{openGLContext, static_cast<const char*>(mem.getData())};
    }
};

#endif /* ShapeFactory_h */
