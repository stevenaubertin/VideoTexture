//
//  MarkerData.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef MarkerData_h
#define MarkerData_h

#include "AABB.h"

template<class POINT_PRECISION_T, class ID_TYPE=int>
struct MarkerData{
    using point_precision_t = POINT_PRECISION_T;
    using bounding_box_t = AABB<point_precision_t>;
    using point_t = typename bounding_box_t::point_t;
    using id_t = ID_TYPE;

    //TODO faire de quoi ici et mettre des trucs privates maybe ??? blaublabli
    id_t id;
    point_t centroid;
    bounding_box_t boundingBox;
};


#endif /* MarkerData_h */
