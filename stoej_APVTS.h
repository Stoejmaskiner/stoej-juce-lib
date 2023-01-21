/*
  ==============================================================================

    stoej_APVTS.h
    Created: 20 Jan 2023 5:01:04pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "stoej_params.h"
#include "gui/stoej_Theming.h"

// TODO: hide this implementation in a cpp file
#define STOEJ_SET_THEME_COLOR_(vt, name) \
vt.setProperty(name::id, name::default_value, nullptr);

namespace stoej {

    // an extension to juce::AudioProcessorValueTreeState that defines some default parameters
    // and attributes used in stoej components.
    // It is optional to use it, but if these values aren't defined, components will fall back
    // to hard-coded values.
    class APVTS : public juce::AudioProcessorValueTreeState {
    public:
        APVTS(
            juce::AudioProcessor& processorToConnectTo, 
            juce::UndoManager* undoManagerToUse, 
            const juce::Identifier& valueTreeType, 
            ParameterLayout parameterLayout
        ) 
        : 
        juce::AudioProcessorValueTreeState(
            processorToConnectTo,
            undoManagerToUse,
            valueTreeType,
            std::move(this->create_default_layout_helper(std::move(parameterLayout)))
        ) {

            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::text_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::text_inverted);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::text_secondary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::foreground_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::background_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::background_secondary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::fill_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::fill_secondary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::light_theme::scope_background);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::text_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::text_inverted);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::text_secondary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::foreground_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::background_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::background_secondary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::fill_primary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::fill_secondary);
            STOEJ_SET_THEME_COLOR_(this->state, theme_colours::dark_theme::scope_background);
        }

    private:
        static ParameterLayout create_default_layout_helper(ParameterLayout layout) {
            layout.add(create_unique_param_bool(parameters::internal_use_dark_theme));
            return layout;
        }
    };
}

#undef STOEJ_SET_THEME_COLOR_