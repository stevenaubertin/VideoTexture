//
//  TextureBase.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef TextureBase_h
#define TextureBase_h

#include <type_traits>
#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../Util/static.h"

struct static_texture_tag{};
struct dynamic_texture_tag{};

struct image_texture_tag{};
struct procedural_texture_tag{};

struct colored_texture_tag : static_texture_tag{};

struct static_image_texture_tag : static_texture_tag, image_texture_tag{};
struct dynamic_image_texture_tag : dynamic_texture_tag, image_texture_tag{};

struct video_texture_tag : dynamic_image_texture_tag{};

struct static_procedural_texture_tag : static_texture_tag, procedural_texture_tag{};
struct dynamic_procedural_texture_tag : dynamic_texture_tag, procedural_texture_tag{};



class TextureBase;
template<class T>
struct texture_traits{
    //static_assert(std::is_base_of<T, TextureBase>::value, "Class must be of base type TextureBase.");
    using texture_tag = typename T::texture_tag;
    
    using is_static = typename bool_type<std::is_base_of<static_texture_tag, texture_tag>::value>::type;
    using is_dynamic = typename bool_type<std::is_base_of<dynamic_texture_tag, texture_tag>::value>::type;
    using is_image = typename bool_type<std::is_base_of<image_texture_tag, texture_tag>::value>::type;
    using is_procedural = typename bool_type<std::is_base_of<procedural_texture_tag, texture_tag>::value>::type;
    
    static_assert(SymetricCondition<is_static, is_dynamic>::value, "Texture can't be static and dynamic at the same time.");
    static_assert(SymetricCondition<is_image, is_procedural>::value || (!is_image::value && !is_procedural::value), "Texture can't be an image and procedural");
};

struct TextureBase{
    using texture_tag = static_texture_tag;
    String name_;
    
    TextureBase(const String& name= String::empty) : name_{name}{}
    virtual ~TextureBase() {}
    virtual bool applyTo (OpenGLTexture&) = 0;
};

#endif /* TextureBase_h */
