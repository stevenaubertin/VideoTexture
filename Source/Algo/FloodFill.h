//
//  FloodFill.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef FloodFill_h
#define FloodFill_h

#include "../Util/node.h"
#include "../../JuceLibraryCode/JuceHeader.h"
#include <list>

class ImageInvalidException{};

template<class NODE_T=node<>, class PRECISION_POINT_T=float, class POINT_T = Point<PRECISION_POINT_T>>
class FloodFill{
    using point_t = POINT_T;
    using value_type = PRECISION_POINT_T;
    using node_t = NODE_T;
    using label = typename node_t::label;

    enum{
        NOT_VISITED,
        VISITED
    };
    
    struct border_point : public std::pair<point_t, node_t*>{
        inline point_t& getPt()const noexcept{
            return std::get<0>(*this);
        }
        inline node_t* getRegion()const noexcept{
            return std::get<1>(*this);
        }
        inline value_type getY()noexcept{
            return getPt().getY();
        }
        inline value_type getX()noexcept{
            return getPt().getX();
        }
        inline void setY(value_type val)noexcept{
            getPt().setY(val);
        }
        inline void setX(value_type val)noexcept{
            getPt().setX(val);
        }
        inline value_type addX(value_type val)noexcept{
            setX(getX() + val);
        }
        inline value_type rmX(value_type val)noexcept{
            setX(getX() - val);
        }
        inline value_type addY(value_type val)noexcept{
            setY(getY() + val);
        }
        inline value_type rmY(value_type val)noexcept{
            setY(getY() - val);
        }
    };
    
    std::list<border_point> currentRegion;
    std::list<border_point> nextRegion;
    Image& img_;
    
    //---- Some Helpers
    static void prepareImage(Image& img){
        for(auto i = 0; i < img.getWidth(); ++i){
            for(auto j = 0; j < img.getHeight(); ++j){
                setPixelNOTVisited({i,j}, img);
            }
        }
    }
    template<class PT>
    inline static value_type getY(const PT& p)noexcept{
        return p.getY();
    }
    template<class PT>
    inline static value_type getX(const PT& p)noexcept{
        return p.getX();
    }
    inline static label getLabel(float color)noexcept{
        return color == 0.0f ? node_t::black : node_t::white;
    }
    template<class PT>
    inline static void pop(std::list<border_point>& region, PT& p)noexcept{
        p = region.front();
        region.pop_front();
    }
    inline static void pop(std::list<border_point>& region, border_point& p)noexcept{
        pop(region, std::get<0>(p));
    }
    template<class PT>
    inline static bool outOfBound(const PT& p, const Image& img)noexcept{
        return getY(p) <= 0 || static_cast<unsigned int>(getY(p)) >= img.getHeight() - 1;
    }
    inline static bool outOfBound(const border_point& p, const Image& img)noexcept{
        return outOfBound(p.getPt(), img);
    }
    template<class PT>
    inline static float getPixelColor(const PT& p, Image& img)noexcept{
        return img.getPixelAt(getX(p), getY(p)).getFloatRed();
    }
    inline static float getPixelColor(const border_point& p, Image& img)noexcept{
        return getPixelColor(p.getPt(), img);
    }
    template<class PT>
    inline static void setPixelVisited(const PT& p, Image& img){
        const auto color = img.getPixelAt(p.getX(), p.getY());
        img.setPixelAt(getX(p), getY(p),
                       {color.getFloatRed(), VISITED, color.getFloatBlue()});
    }
    inline static void setPixelVisited(const border_point& p, Image& img){
        setPixelNOTVisited(p.getPt(), img);
    }
    template<class PT>
    inline static void setPixelNOTVisited(const PT& p, Image& img){
        const auto color = img.getPixelAt(p.getX(), p.getY());
        img.setPixelAt(getX(p), getY(p),
                       {color.getFloatRed(), NOT_VISITED, color.getFloatBlue()});
    }
    inline static void setPixelNOTVisited(const border_point& p, Image& img){
        setPixelNOTVisited(p.getPt(), img);
    }
    template<class PT>
    inline static bool isPixelVisited(const PT& p, Image& img){
        return img.getPixelAt(getX(p), getY(p)).getFloatGreen() == VISITED;
    }
    inline static bool isPixelVisited(const border_point& p, Image& img){
        return isPixelVisited(p.getPt(), img);
    }
    template<class PT>
    inline static bool isTargetColor(float targetColor, const PT& p, Image& img)noexcept{
        return targetColor == getPixelColor(p, img);
    }
    inline static bool isTargetColor(float targetColor, const border_point& p, Image& img)noexcept{
        return isTargetColor(targetColor, p, img);
    }
    inline static auto getNewRegion(const border_point& p)noexcept -> decltype(p.getRegion()){
        return p.getRegion();
    }
    inline static bool isNewRegion(const border_point& p)noexcept{
        return getNewRegion(p) == nullptr;
    }
public:
    FloodFill(Image& img)
        : img_{img.isValid() ? img : throw ImageInvalidException{}}{
            prepareImage(img);
    }
    
    void floodFill(node_t* root){
        currentRegion.clear();
        nextRegion.clear();
        
        node_t* parent = nullptr;
        node_t toAdd = nullptr;
        bool isBorder = false;
        float targetColor;
        auto current = std::make_pair<border_point>({0,0}, nullptr);
        
        nextRegion.push_back(current);
        while(!nextRegion.empty()){
            pop(nextRegion, current);
            
            isBorder = false;//we check border for each region
            
            //newly created region
            //this sentinel is use to set parent region
            if(isNewRegion(current)){
                parent = getNewRegion(current);
            }
            else{//already known region but not yet explore
                targetColor = getPixelColor(current, img_);
                
                if(!isPixelVisited(current, img_)){
                    currentRegion.push_back(current);
                    toAdd = new node_t{getLabel(targetColor)};
                    
                    //push sentinel into next region to avoid searching in tree
                    nextRegion.emplace_back({0,0}, toAdd);
                    
                    while(!currentRegion.empty()){
                        pop(currentRegion, current);
                        
                        isBorder |= outOfBound(current, img_);
                        
                        //Check Neighbords
                        if(isTargetColor(targetColor, current, img_) && !isPixelVisited(current, img_)){
                            
                            border_point west{current};
                            for(;getX(west) > 0 && sTargetColor(targetColor, west, img_) &&
                                !isPixelVisited(west, img_);
                                rmX(west, 1));
                            if(getX(west) > 0){
                                if(!isTargetColor(targetColor, west, img_) && !isPixelVisited(west, img_)){
                                    nextRegion.push_back(west);
                                }
                                addX(west, 1);
                            }
                            else if(isPixelVisited(west, img_)){
                                addX(west, 1);
                            }
                            else{
                                isBorder = true;
                                if(!isTargetColor(targetColor, west, img_) && !isPixelVisited(west, img_)){
                                    nextRegion.push_back(west);
                                }
                            }
                            
                            border_point east{current};
                            for(;static_cast<size_t>(east.getX()) < img_.getWidth() && isTargetColor(targetColor, east, img_) && !isPixelVisited(east, img_);east.addX(1));
                            if(static_cast<size_t>(east.x_) < img_.getWidth() && !isTargetColor(targetColor, east, img_) && !isPixelVisited(east, img_)){
                                nextRegion.push_back(east);
                            }
                            if(static_cast<size_t>(east.getX()) >= img_.getWidth()){
                                isBorder = true;
                            }
                            
                            border_point neighbord{east.getX(), current.getY()};
                            for(;neighbord.getX() < east.getX(); neighbord.addX(1)){
                                toAdd->fill(neighbord);
                                setPixelVisited(neighbord, img_);
                                
                                border_point up{neighbord.getX(), neighbord.getY() - 1};
                                if(up.getY() >= 0 && isTargetColor(targetColor, up, img_) && !isPixelVisited(up, img_)){
                                    currentRegion.push_back(up);
                                }
                                
                                border_point down{neighbord.getX(), neighbord.getY() + 1};
                                if(static_cast<size_t>(down.getY()) < img_.getHeight() && isTargetColor(targetColor, down, img_) && !isPixelVisited(down, img_)){
                                    currentRegion.push_bakc(down);
                                }
                            }
                        }
                    }
                    if(isBorder){
                        root->addChildren(toAdd);
                    }
                    else{
                        parent->addChildren(toAdd);
                    }
                }
            }
        }
    }
};


#endif /* FloodFill_h */
