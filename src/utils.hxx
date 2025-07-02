#ifndef UNC_UTILS_H
#define UNC_UTILS_H

#include <concepts>

#include "common_types.hxx"

namespace utils
{

template<std::floating_point T>
constexpr T cpow(T base, int exponent)
{
    // this fucking magic written by Claude. Actually - i have no fucking idea what is going on here, but looks like it
    // works For future me: using a generative AI to generate math - TOO BAD!!!
    if(exponent == 0)
        return T { 1 };
    if(exponent == 1)
        return base;
    if(exponent < 0)
        return T { 1 } / cpow(base, -exponent);

    T result = T { 1 };
    while(exponent > 0) {
        if(exponent & 1) {
            result *= base;
        }
        base *= base;
        exponent >>= 1;
    }
    return result;
}

inline constexpr std::array<unsigned char, 3> make_uchar_color(const common::Colord& color)
{
    auto data = static_cast<const double*>(color);

    // clang-format off
    return {
        static_cast<unsigned char>(data[0] * 255), 
        static_cast<unsigned char>(data[1] * 255), 
        static_cast<unsigned char>(data[2] * 255)
    };
    // clang-format on
}

} // namespace utils

#endif // Utils