/*
  ==============================================================================

    stoej_compile_time_utils.h
    Created: 27 Aug 2022 5:34:56pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <gcem.hpp>

namespace stoej {
    template<double db> constexpr double const_db2a() {
        return gcem::pow<double, double>(10., db / 20.);
    }

    template<double a> constexpr double const_a2db() {
        return 20. * gcem::log10(a);
    }
}