//
//  Math.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef Math_h
#define Math_h

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Util/Random.h"
#include "../Util/Image.h"

#include <algorithm>
#include <type_traits>

template<class T>
constexpr typename std::enable_if<!std::is_integral<T>::value,T>::type
clamp(const T& val, const T& min, const T& max)noexcept{
    return std::max(std::min(val, max), min);
}
template<class T>
constexpr typename std::enable_if<std::is_integral<T>::value,T>::type
clamp(T val, T min, T max)noexcept{
    return std::max(std::min(val, max), min);
}

template<class T>
constexpr T abs(T val)noexcept{
    return val > 0.0 ? val : -val;
}


void KMeansSegmentation(Image& img){
    for(auto x = 0; x < img.getWidth(); ++x){
        for(auto y = 0; y < img.getHeight(); ++y){
            const auto pxl = img.getPixelAt(x,y);
            img.setPixelAt(x,y, pxl.getBrightness() > 0.5 ? Colours::white : Colours::black);
        }
    }
    return;
    
    auto cp = img.createCopy();
    double lbl1 = -1.0;
    double lbl2 = -1.0;
    float class1;
    float class2;
    
    do{//Get 2 random pixel wich are diffrent
        class1 = cp.getPixelAt(random_int(0,img.getWidth()), random_int(0,img.getHeight())).getBrightness();
        class2 = cp.getPixelAt(random_int(0,img.getWidth()), random_int(0,img.getHeight())).getBrightness();
    }while(class1==class2);
    
    // Make classe1 < classe2 for contiguous lighting results
    if(class1 > class2){
        std::swap(class1, class2);
    }
    
    //size_t n = 1;
    while(class1 != lbl1 && class2 != lbl2){
        for(auto x = 0; x < cp.getWidth(); ++x){
            for(auto y = 0; y < cp.getHeight(); ++y){
                const auto pxl = cp.getPixelAt(x,y);
                img.setPixelAt(x,y,
                    abs(pxl.getBrightness() - class2) < abs(pxl.getBrightness() - class1) ?
                        Colours::white : Colours::black);
            }
        }
        double sum1 = 0;
        double sum2 = 0;
        lbl1 = class1;
        lbl2 = class2;
        class1 = 0.0f;
        class2 = 0.0f;
        for(auto x = 0; x < cp.getWidth(); ++x){
            for(auto y = 0; y < cp.getHeight(); ++y){
                const auto pxl = cp.getPixelAt(x,y);
                if(cp.getPixelAt(x,y)==Colours::white){
                    class2 += pxl.getBrightness();
                    ++sum2;
                }
                else{
                    class1 += pxl.getBrightness();
                    ++sum1;
                }
            }
        }
        class1 /= sum1;
        class2 /= sum2;
    }
}

#endif /* Math_h */
