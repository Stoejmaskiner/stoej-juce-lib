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

#define STOEJ_SET_THEME_COLOR_(vt, name) \
vt.setProperty(name::id, name::default_value, nullptr);

namespace stoej {
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
            std::move(parameterLayout)
        ) {
            this->createAndAddParameter(UniqueParamBool(parameters::internal_use_dark_theme));

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
    };
}

#undef STOEJ_SET_THEME_COLOR_