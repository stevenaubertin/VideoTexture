//
//  Random.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-17.
//
//

#ifndef Random_h
#define Random_h

#include <random>

template<int min, int max>
static int random_int(){
    static std::random_device rd;
    static std::mt19937 prng{rd()};
    static std::uniform_int_distribution<> d{min, max};
    return d(prng);
}

static int random_int(int min, int max){
    static std::random_device rd;
    static std::mt19937 prng{rd()};
    static std::uniform_int_distribution<> d{min, max};
    return d(prng);
}

#endif /* Random_h */
