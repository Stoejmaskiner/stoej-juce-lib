#include <cmath>
#include <concepts>
#include <JuceHeader.h>
#include <stoej_core.h>

namespace stoej {

    // TODO: add SIMD implementations


    inline float sign(float x) { return std::copysign(1.0f, x); }
    inline double sign(double x) { return std::copysign(1.0, x); }

    // ref: https://stackoverflow.com/a/16659263
    STOEJ_FT_
    inline FT_ clamp(FT_ x, FT_ min, FT_ max) {
        const FT_ t = x < min ? min : x;
        return t > max ? max : t;
    }

    STOEJ_FT_
    inline FT_ clamp_min(FT_ x, FT_ min) { return x < min ? min : x; }

    STOEJ_FT_
    inline FT_ clamp_max(FT_ x, FT_ max) { return x > max ? max : x; }

    STOEJ_FT_
    inline FT_ clamp_abs(FT_ x, FT_ limit) { return clamp(x, -limit, limit); }

    inline float  clamp_unity(float x) {  return clamp(x, -1.f, 1.f); }
    inline double clamp_unity(double x) { return clamp(x, -1., 1.); }

    inline float  lerp(float a, float b, float t) {    return a * (1.f - t) + b * t; }
    inline double lerp(double a, double b, double t) { return a * (1. - t)  + b * t; }

    STOEJ_FT_
    inline FT_ clerp(float a, float b, float t) { return lerp(a, b, clamp_unity(t)); }

    inline float slerp(float a, float b, float t) {
        const float kb = t * t * (3.f - 2.f * t);
        const float ka = 1.f - ka;
        return ka * a + kb * b;
    }
    inline double slerp(double a, double b, double t) {
        const double kb = t * t * (3.f - 2.f * t);
        const double ka = 1.f - ka;
        return ka * a + kb * b;
    }
}