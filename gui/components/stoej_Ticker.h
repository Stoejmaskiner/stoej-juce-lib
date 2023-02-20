/*
  ==============================================================================

    stoej_Ticker.h
    Created: 3 Jan 2023 7:35:27pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "gui/components/stoej_component.h"
#include "stoej_Types.h"
#include "utils/stoej_math.h"
#include "binary_data/stoej_Fonts.h"
#include "utils/stoej_graphics_utils.h"

namespace stoej {
    class Ticker : public juce::MouseListener, public stoej::FloatComponent<juce::Label> {
    public:
        // enum SliderVariant { minimal, mod };
        // enum SliderSize {};
        //enum SliderDirection { vertical, horizontal };

        Ticker(stoej::APVTS* apvts, stoej::ThemeManager& theme_manager, const juce::String& component_name);
        std::variant<float, DynamicSize2> getPreferredHeight() override { return { 24.0f }; }
        std::variant<float, DynamicSize2> getPreferredWidth() override { return { fill_parent }; }
        void mouseEnter(const juce::MouseEvent& event) override;
        void mouseExit(const juce::MouseEvent& event) override;
        //void resized() override;
        void paint(juce::Graphics& g) override;
        //void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    private:
        juce::String active_tooltip_ = "";
        //Box bounding_box_;
        //juce::Label label_box_;
        //juce::Label value_box_;
    };
}