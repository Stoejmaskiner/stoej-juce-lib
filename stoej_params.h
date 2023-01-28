/*
  ==============================================================================

    stoej_params.h
    Created: 19 Jan 2023 11:56:19pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

namespace stoej {
    struct BoolParamInfo {
        const char* id;
        const char* name;
        const bool init;
    };

    struct FloatParamInfo {
        const juce::String id;
        const juce::String name;
        const float init;
        const float range_0 = 0.0f;
        const float range_1 = 1.0f;
        const float skew = 1.0f;
        const float step_size = 0.0f;
        const bool use_symmetric_skew = false;
    };

    // converts a stoej::FloatParamInfo to a std::make_unique<juce::AudioParameterFloat>
    inline auto create_unique_param_float(FloatParamInfo p_info) {
        return std::make_unique<juce::AudioParameterFloat>(
            p_info.id,
            p_info.name,
            juce::NormalisableRange<float>(
                p_info.range_0,
                p_info.range_1,
                p_info.step_size,
                p_info.skew,
                p_info.use_symmetric_skew),
            p_info.init);
    }

    // converts a stoej::BoolParamInfo to a std::make_unique<juce::AudioParameterBool>
    inline auto create_unique_param_bool(BoolParamInfo p_info) {
        return std::make_unique<juce::AudioParameterBool>(
            p_info.id,
            p_info.name,
            p_info.init);
    }
}

namespace stoej {
    namespace strings {
        namespace apvts_children {
            inline const juce::Identifier internal_params_state = "kxkpqeZH8Nt3qKgwdvrRp";
        }
        namespace internal_params {
            inline const std::string use_dark_theme = "internal_params::use_dark_theme";
        }
    }

    // TODO: can probably remove a layer of indirection in some places if you reuse the string as the id, same with properties
    inline const std::map<std::string, BoolParamInfo> bool_params = {
        {strings::internal_params::use_dark_theme, { "Y0mDh-wQe8r6rXT6bA_QD", "{internal - use dark theme}", false }}
    };
    
    // instructions:
    // to add a new parameter you need:
    // - a unique identifier, which must start with `internal_`
    // - a unique NanoID, which the APVTS uses internally, also DAWS sometimes. Note that it must start with a letter (discard NanoIDs that don't)
    // - a unique name string (which DAWs use) in the format `{internal - some name}`
}