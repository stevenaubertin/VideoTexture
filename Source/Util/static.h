//
//  static.h
//  OpenGLAppExample
//
//  Created by Steven Aubertin on 2016-04-05.
//
//

#ifndef static_h
#define static_h

template<bool>struct bool_type{};
template<>struct bool_type<true>{using type = std::true_type;};
template<>struct bool_type<false>{using type = std::false_type;};

template<class T1, class T2>
struct SymetricCondition{
    static_assert(std::is_base_of<T1, std::true_type>::value || std::is_base_of<T1, std::false_type>::value,
                  "Class T1 must be either true_type of false_type");
    static_assert(std::is_base_of<T2, std::true_type>::value || std::is_base_of<T2, std::false_type>::value,
                  "Class T2 must be either true_type of false_type");
    using type = typename bool_type<(T1::value && !T2::value) || (!T1::value && T2::value)>::type;
    static const bool value = type::value;
};

#endif /* static_h */
