#pragma once
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

    inline float  lerp(float a, float b, float t) { return a * (1.f - t) + b * t; }
    inline double lerp(double a, double b, double t) { return a * (1. - t) + b * t; }
    template<typename T> juce::Point<T> lerp(juce::Point<T> a, juce::Point<T> b, double t) { return a * (1. - t) + b * t; }
    template<typename T> juce::Line<T> lerp(juce::Line<T> a, juce::Line<T> b, double t) {
        return juce::Line<T>(
            lerp(a.getStart(), b.getStart(), t),
            lerp(a.getEnd(), b.getEnd(), t)
        );
    }
    template<typename T> juce::Rectangle<T> lerp(juce::Rectangle<T> a, juce::Rectangle<T> b, double t) {
        return juce::Rectangle<T>(
            lerp(a.getTopLeft(), b.getTopLeft(), t),
            lerp(a.getTopRight(), b.getTopRight(), t),
            lerp(a.getBottomLeft(), b.getBottomLeft(), t),
            lerp(a.getBottomRight(), b.getBottomRight(), t)
        );
    }

    STOEJ_FT_
    inline FT_ clerp(FT_ a, FT_ b, FT_ t) { return lerp(a, b, clamp_max(t, FT_(1.0))); }

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