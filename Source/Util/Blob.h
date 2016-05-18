//
//  Blob.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef Blob_h
#define Blob_h

#include "MarkerData.h"

#include <vector>
#include <algorithm>

template<class POINT_PRECISION_T=float, class POINT_T=Point<POINT_PRECISION_T>>
class Blob{
public:
    using positions_collections_t = std::vector<POINT_T>;
    using point_precision_t = POINT_PRECISION_T;
    using bounding_box_t = AABB<point_precision_t>;
    using point_t = typename bounding_box_t::value_type;
private:
    positions_collections_t pos_;
    bounding_box_t boundingBox_;
    point_t centroid_;
public:
    Blob(const positions_collections_t& pos)
        : pos_{pos}{
            computeBoundingBox();
            computeCentroid();
    }
    void computeBoundingBox()noexcept{
        jassert(!pos_.empty());
        std::for_each(std::begin(pos_), std::end(pos_), [&](point_t& pt){
            boundingBox_.Top = {
                std::min(pt.getX(), boundingBox_.Left),
                std::min(pt.getY(), boundingBox_.Top)
            };
            boundingBox_.Bottom = {
                std::max(pt.getX(), boundingBox_.Right),
                std::max(pt.getY(), boundingBox_.Bottom)
            };
        });
    }
    void computeCentroid()noexcept{
        centroid_ = {
            boundingBox_.getWidth() / 2.0,
            boundingBox_.getHeight() / 2.0,
        };
        jassert(centroid_.getX() && centroid_.getY());
    }
    const bounding_box_t getBoundingBox()const noexcept{
        return boundingBox_;
    }
    const point_t getCentroid()const noexcept{
        return centroid_;
    }
};

#endif /* Blob_h */
