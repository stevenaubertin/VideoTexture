//
//  AABB.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef AABB_h
#define AABB_h

#include "../../JuceLibraryCode/JuceHeader.h"

/*
    AABB
    A bounding box formed by 2 points.
 
    top
    * ------ *
    |        |
    |        |
    |        |
    * ------ *
             bottom
 */

template<class T=float>
struct AABB{
    using point_t = Point<T>;
    using value_type = T;
private:
    point_t top_;
    point_t bottom_;
public:
    constexpr AABB(const point_t& top, const point_t& bottom)noexcept
        : top_{top}, bottom_{bottom}{
    }
    constexpr AABB(point_t&& top, point_t&& bottom)noexcept
        : top_{std::move(top)}, bottom_{std::move(bottom)}{
            top = {};
            bottom = {};
    }
    constexpr AABB(value_type top, value_type bottom, value_type left, value_type right)noexcept
        : top_{left,top}, bottom_{right,bottom}{
    }
    constexpr value_type& getTop() const noexcept{
        return top_.getY();
    }
    constexpr value_type& getLeft()const noexcept{
        return top_.getX();
    }
    constexpr value_type& getBottom()const noexcept{
        return bottom_.getY();
    }
    constexpr value_type& getRight()const noexcept{
        return bottom_.getX();
    }
    constexpr value_type getWidth()const noexcept{
        return getRight() - getLeft();
    }
    constexpr value_type getHeight() const noexcept{
        return getBottom() - getTop();
    }
};

#endif /* AABB_h */
