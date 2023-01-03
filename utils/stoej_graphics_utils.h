/*
  ==============================================================================

    stoej_graphics.h
    Created: 1 Sep 2022 1:50:31am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include "utils/stoej_math.h"

// TODO: rename to gui utils, as "graphics" implies OpenGL

namespace stoej {
	constexpr double PT_2_PX = 1.333333;
	constexpr double PX_2_PT = 0.75;

    // FIXME: is this a memory leak?
    inline std::string format_float_hertz(float val) {
        jassert(val >= 0.0f);

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

    // FIXME: is this a memory leak?
    inline std::string format_float_percent(float val) {
        //jassert(val >= 0.0f);

        // TODO: tiny values
        return std::format("{:.2f} %", val * 100.f);
        //return "";
    }

    // FIXME: is this a memory leak?
    inline std::string format_float_no_unit(float val) {
        //jassert(val >= 0.0f);

        // TODO: tiny values
        return std::format("{:.3f}", val);
        //return "";
    }

    // FIXME: is this a memory leak?
    inline std::string format_float_level2db(float val) {
        jassert(val >= 0.0f);

        if (val == 0.0f) {
            return "-inf";
        }

        // TODO: tiny values
        return std::format("{:.2f} dB", stoej::a2db(val));
        //return "";
    }


    inline void draw_rect_f(juce::Graphics& g, juce::Rectangle<float> r, float thickness) {
        g.drawRoundedRectangle(r, 0.0f, thickness);
    }

    inline juce::Rectangle<float> int_rect_2_float_rect(juce::Rectangle<int> r) {
        return juce::Rectangle<float>(
            float(r.getTopLeft().getX()),
            float(r.getTopLeft().getY()),
            float(r.getWidth()),
            float(r.getHeight()));
    }

    [[deprecated("TODO: undeprecate this when you have fixed all the janky places where you used this as a crutch")]]
    inline juce::Rectangle<int> float_rect_2_int_rect(juce::Rectangle<float> r) {
        return juce::Rectangle<int>(
            int(r.getTopLeft().getX()),
            int(r.getTopLeft().getY()),
            int(r.getWidth()),
            int(r.getHeight()));
    }


}