/*
  ==============================================================================

    stoej_Slider.h
    Created: 15 Dec 2022 9:03:00pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "gui/components/stoej_component.h"

namespace stoej {
    class StoejSlider : stoej::FloatComponent<juce::Slider> {
    public:
        // enum SliderVariant { minimal, mod };
        // enum SliderSize {};

        StoejSlider(const juce::String& component_name, const char* label, )
        std::variant<float, DynamicSize2> getPreferredHeight() override;
        std::variant<float, DynamicSize2> getPreferredWidth() override;
        //void resized() override;
        //void paint(juce::Graphics&) override {}
        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    private:
        const char* label_;
        const juce::Font& font_;

        bool is_inverted_;
        //Box bounding_box_;
    };
}