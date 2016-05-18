//
//  DynamixBouncingNumberTexture.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef DynamixBouncingNumberTexture_h
#define DynamixBouncingNumberTexture_h

#include "DynamicTexture.h"

struct DynamicBouncingNumberTexture : public virtual DynamicTexture{
    using texture_tag = dynamic_image_texture_tag;
    
    //==============================================================================
    // This is basically a sawtooth wave generator - maps a value that bounces between
    // 0.0 and 1.0 at a random speed
    class BouncingNumber{
    protected:
        double speed, phase;
    public:
        BouncingNumber()
            : speed (0.0004 + 0.0007 * Random::getSystemRandom().nextDouble()),
              phase (Random::getSystemRandom().nextDouble()){
        }
        float getValue() const{
            const double v = fmod (phase + speed * Time::getMillisecondCounterHiRes(), 2.0);
            return static_cast<float>(v >= 1.0 ? (2.0 - v) : v);
        }
    };
    
    struct SlowerBouncingNumber: public BouncingNumber{
        SlowerBouncingNumber(){
            speed *= 0.3;
        }
    };
    
    Image image;
    BouncingNumber x, y;
    
    bool applyTo (OpenGLTexture& texture) override{
        const int size = 128;
        
        if (! image.isValid()){
            image = Image (Image::ARGB, size, size, true);
        }
        
        {
            Graphics g (image);
            g.fillAll (Colours::lightcyan);
            
            g.setColour (Colours::darkred);
            g.drawRect (0, 0, size, size, 2);
            
            g.setColour (Colours::green);
            g.fillEllipse (x.getValue() * size * 0.9f, y.getValue() * size * 0.9f, size * 0.1f, size * 0.1f);
            
            g.setColour (Colours::black);
            g.setFont (40);
            g.drawFittedText (String (Time::getCurrentTime().getMilliseconds()), image.getBounds(), Justification::centred, 1);
        }
        
        texture.loadImage (image);
        return true;
    }
};

#endif /* DynamixBouncingNumberTexture_h */
