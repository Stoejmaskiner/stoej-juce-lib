/*
  ==============================================================================

    stoej_graphics.h
    Created: 1 Sep 2022 1:50:31am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

namespace stoej {
	constexpr double PT_2_PX = 1.333333;
	constexpr double PX_2_PT = 0.75;

    // FIXME: is this a memory leak?
    inline std::string format_float_hertz(float val) {
        jassert(val >= 0.0f);

        /*
        // Hz
        if (val < 1000.0f) {
            return std::format("{:3f} Hz", val);
        }
        // kHz
        return std::format("{:3f} kHz", val);
        */

        // TODO: formatting for values smaller than 10 Hz
        if (val < 100.f) {
            return std::format("{:.2f} Hz", val);
        }
        if (val < 1000.f) {
            return std::format("{:.1f} Hz", val);
        }
        if (val < 10000.f) {
            return std::format("{:.2f} kHz", val / 1000.f);
        }
        if (val < 100000.f) {
            return std::format("{:.1f} kHz", val / 1000.f);
        }
        return "";
    }
}