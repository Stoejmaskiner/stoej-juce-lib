/*
  ==============================================================================

    stoej_value.h
    Created: 21 Dec 2022 8:33:45pm
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
    class Value : public stoej::FloatComponent<juce::Slider> {
    public:
        // enum SliderVariant { minimal, mod };
        // enum SliderSize {};
        //enum SliderDirection { vertical, horizontal };

        Value(stoej::ThemedAPVTS&, const juce::String& component_name, const char* label, ValueUnit unit);
        std::variant<float, DynamicSize2> getPreferredHeight() override { return { 48.0f }; }
        std::variant<float, DynamicSize2> getPreferredWidth() override { return { 48.0f }; }
        void resized() override;
        void paint(juce::Graphics& g) override;
        //void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    private:
        const char* label_;
        ValueUnit unit_;
        //Box bounding_box_;
        //juce::Label label_box_;
        //juce::Label value_box_;
    };
}