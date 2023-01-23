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
#include "utils/stoej_cpp_utils.h"
#include "stoej_properties.h"

// TODO: hide this implementation in a cpp file
#define STOEJ_SET_THEME_COLOR_(vt, name) \
vt.setProperty(name.id, name.default_value, nullptr);

namespace stoej {

    // an extension to juce::AudioProcessorValueTreeState that defines some default parameters
    // and attributes used in stoej components.
    class ThemedAPVTS : public juce::AudioProcessorValueTreeState {
    public:
        ThemedAPVTS(
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
            auto theme_state = this->state.getOrCreateChildWithName(strings::apvts_children::theme_state, nullptr);
            for (auto const& [_, val] : stoej::theme_colors) {
                theme_state.setProperty(val.id, val.init, nullptr);
            }
            auto internal_properties_state = this->state.getOrCreateChildWithName(strings::apvts_children::internal_properties_state, nullptr);
            for (auto const& [_, val] : stoej::properties) {
                internal_properties_state.setProperty(val.id, val.init, nullptr);
            }
        }

        float getParameterFloatOr(juce::StringRef id, float default_value) {
            auto maybe_val = this->getRawParameterValue(id);
            return maybe_val ? float(*maybe_val) : default_value;
        }

        bool getParameterBoolOr(juce::StringRef id, bool default_value) {
            auto maybe_val = this->getRawParameterValue(id);
            return maybe_val ? (*maybe_val >= 0.5f) : default_value;
        }

        juce::Colour getPropertyThemeColor(const stoej::PropertyInfo& info) {
            juce::int64 maybe_val = this->state.getProperty(info.id);
            return juce::Colour(maybe_val ? maybe_val : juce::int64(info.init));
        }

    private:
        static ParameterLayout create_default_layout_helper(ParameterLayout layout) {
            for (auto const& [_, val] : stoej::bool_params) {
                layout.add(create_unique_param_bool(val));
            }
            //for (auto const& [_, val] : stoej::float_params) {
            //
            //}
            return layout;
        }
    };
}

#undef STOEJ_SET_THEME_COLOR_