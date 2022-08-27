/*
  ==============================================================================

    stoej_xfade_coeffs.h
    Created: 27 Aug 2022 11:43:59am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <stoej_core.h>
#include <stoej_math.h>
#include <utility>
#include <JuceHeader.h>
#include <gcem.hpp>
#include "utils/stoej_compile_time_utils.h"

namespace stoej {

    using Approx_ = juce::dsp::FastMathApproximations;
    constexpr double HALF_PI_ = juce::MathConstants<double>::halfPi;

    STOEJ_FT_ struct Coeffs { FT_ a; FT_ b; };

    STOEJ_FT_
    Coeffs<FT_> xfade_linear_coeffs(FT_ t) {
        return Coeffs<FT_>{ .a = t, .b = FT_(1.0)};
    }

    STOEJ_FT_ const auto xfade_6db_coeffs = xfade_linear_coeffs<FT_>;
    // aliased for API consistency


    STOEJ_FT_
    Coeffs<FT_> xfade_3db_coeffs(FT_ t) {
        return Coeffs<FT_> {
            .a = Approx_::cos(FT_(HALF_PI_) * t),
            .b = Approx_::cos(FT_(HALF_PI_) * (FT_(1.0) - t)),
        };
    }

    STOEJ_FT_
    Coeffs<FT_> xfade_4p5db_coeffs(FT_ t) {
        const FT_ ca = Approx_::cos(FT_(HALF_PI_) * t);
        const FT_ cb = Approx_::cos(FT_(HALF_PI_) * (FT_(1.0) - t));
        return Coeffs<FT_> {
            .a = ca * std::sqrt(ca), // faster than std::pow(ca, 1.5) in benchmark
            .b = cb * std::sqrt(cb),
        };
    }

    /// <summary>
    /// this function will generate coefficients for any desired crossover gain,
    /// the crossover gain is provided at compile time and part of the computation
    /// is also at compile time, so this function is extremely fast. It is however
    /// not completely accurate, but the error is at most -0.19 dB for xover_gain
    /// in [-6, -3]
    /// </summary>
    template<typename FT_, double xover_gain_db> requires std::floating_point<FT_>
    Coeffs<FT_> fast_xfade_coeffs(FT_ t) {
        constexpr double v = stoej::const_db2a<xover_gain_db>();
        constexpr double alpha = 4. * v - 2.;
        constexpr double beta = 1. - alpha;
        const FT_ one_min_t = FT_(1.0) - t;
        return Coeffs<FT_> {
			.a = FT_(1.) - FT_(alpha) * t * t - FT_(beta) * t,
            .b = FT_(1.) - FT_(alpha) * one_min_t * one_min_t - FT_(beta) * one_min_t,
        };
    }

    STOEJ_FT_
    void xfade (FT_* dst, const FT_* src, Coeffs<FT_> coeffs, int len) {
	    juce::FloatVectorOperationsBase<FT_,int>::multiply(dst, coeffs.a, len);
        juce::FloatVectorOperationsBase<FT_,int>::addWithMultiply(dst, src, coeffs.b, len);
    }
}