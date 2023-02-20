/*
  ==============================================================================

    stoej_graphics.h
    Created: 1 Sep 2022 1:50:31am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include "utils/stoej_math.h"
#include "gui/stoej_Colours.h"

// TODO: rename to gui utils, as "graphics" implies OpenGL

// create a juce::Drawable from binary image data (SVG, etc...)
#define STOEJ_DRAWABLE_IMG(s) (stoej::prepare_drawable(juce::Drawable::createFromImageData(s,s##Size)))

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

    inline void fill_rect_f(juce::Graphics& g, juce::Rectangle<float> r) {
        g.fillRoundedRectangle(r, 0.0f);
    }

    [[deprecated("use juce::Rectangle.toFloat() instead")]]
    inline juce::Rectangle<float> int_rect_2_float_rect(juce::Rectangle<int> r) {
        return juce::Rectangle<float>(
            float(r.getTopLeft().getX()),
            float(r.getTopLeft().getY()),
            float(r.getWidth()),
            float(r.getHeight()));
    }

    [[deprecated("use juce::Rectangle.toInt() instead")]]
    inline juce::Rectangle<int> float_rect_2_int_rect(juce::Rectangle<float> r) {
        return juce::Rectangle<int>(
            int(r.getTopLeft().getX()),
            int(r.getTopLeft().getY()),
            int(r.getWidth()),
            int(r.getHeight()));
    }

    // TODO: janky workaround to there not being a "replace all colours" function in JUCE.
    // it replaces common SVG colours with stoej::Colours::meta_unassigned
    static std::unique_ptr<juce::Drawable> prepare_drawable(std::unique_ptr<juce::Drawable> drawable) {
        drawable->replaceColour(juce::Colours::black, stoej::Colours::meta_unassigned);
        return drawable;
    }

    
}