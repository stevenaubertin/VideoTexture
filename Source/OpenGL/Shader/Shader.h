//
//  Shaders.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef Shaders_h
#define Shaders_h

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "Attributes.h"
#include "Uniforms.h"
#include "ShaderPreset.h"

class ShaderFactory;
class Shader{
    ScopedPointer<OpenGLShaderProgram> prog_;
    ScopedPointer<Attributes> attributes_;
    ScopedPointer<Uniforms> uniforms_;
    String statusText_;
    bool isValid_;
    
    Shader(OpenGLContext& openGLContext)
        : prog_{new OpenGLShaderProgram (openGLContext)}, isValid_{true}{
    }
    
public:    
    const String& getStatus()const noexcept{
        return statusText_;
    }
    const String& getLastError()const noexcept{
        return prog_->getLastError();
    }
    double getLanguageVersion()const noexcept{
        jassert(isValid());
        return prog_->getLanguageVersion();
    }
    GLuint getProgramId()const noexcept{
        jassert(isValid());
        return prog_->getProgramID();
    }
    void use()const noexcept{
        jassert(isValid());
        prog_->use();
    }
    Attributes& getAttributes()const noexcept{
        jassert(isValid());
        return *attributes_;
    }
    Uniforms& getUniforms()const noexcept{
        jassert(isValid());
        return *uniforms_;
    }
    OpenGLShaderProgram::Uniform& getProjectionMatrix()const noexcept{
        jassert(isValid());
        return *getUniforms().projectionMatrix;
    }
    OpenGLShaderProgram::Uniform& getViewMatrix()const noexcept{
        jassert(isValid());
        return *getUniforms().viewMatrix;
    }
    void setTexture(GLint n = 0){
        jassert(isValid());
        const auto& u = getUniforms();
        if (u.texture != nullptr)
            u.texture->set(n);
    }
    void setLightPosition(GLfloat n1, GLfloat n2, GLfloat n3, float n4){
        jassert(isValid());
        const auto& u = getUniforms();
        if (u.lightPosition != nullptr)
            u.lightPosition->set(n1,n2,n3,n4);
    }
    bool isValid()const noexcept{
        return isValid_;
    }
    operator bool() const noexcept{
        return isValid();
    }
    
    friend class ShaderFactory;
};

struct ShaderFactory{
    static ScopedPointer<Shader> create(OpenGLContext& context, const ShaderPreset& p){
        return create(context, p.getVertexShader(), p.getFragmentShader());
    }
    static ScopedPointer<Shader> create(OpenGLContext& context,
                                        const char* vertexShader,
                                        const char* fragmentShader){
        ScopedPointer<Shader> shader{new Shader{context}};
        
        if(shader->prog_->addVertexShader(OpenGLHelpers::translateVertexShaderToV3(vertexShader)) &&
           shader->prog_->addFragmentShader(OpenGLHelpers::translateFragmentShaderToV3(fragmentShader)) &&
           shader->prog_->link()){
            
            shader->attributes_ = new Attributes (context, *shader->prog_);
            shader->uniforms_   = new Uniforms (context, *shader->prog_);
            shader->statusText_ = "GLSL: v" + String (OpenGLShaderProgram::getLanguageVersion(), 2);
        }
        else{
            shader->statusText_ = shader->getLastError();
            shader->isValid_ = false;
        }
        
        return shader;
    }
};

#endif /* Shaders_h */






