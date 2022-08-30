/*
  ==============================================================================

    stoej_juce_utils.hpp
    Created: 31 Jul 2022 2:33:41am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <concepts>

namespace stoej {


    struct BoolParamInfo {
        const char* id;
        const char* name;
        const bool init;
    };

    struct FloatParamInfo {
	    const char* id;
        const char* name;
        const float init;
        const float range_0 = 0.0f;
        const float range_1 = 1.0f;
        const float skew = 1.0f;
        const float step_size = 0.0f;
        const bool use_symmetric_skew = false;
    };

    /// converts a stoej::FloatParamInfo to a std::make_unique<juce::AudioParameterFloat>
    inline auto UniqueParamFloat(FloatParamInfo p_info) { 
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

    /// converts a stoej::BoolParamInfo to a std::make_unique<juce::AudioParameterBool>
    inline auto UniqueParamBool(BoolParamInfo p_info) {
        return std::make_unique<juce::AudioParameterBool>(
            p_info.id,
            p_info.name,
            p_info.init);
    }

    /// convert juce::AudioBuffer to juce::ProcessContextReplacing
    /// to reduce boilerplate
    [[deprecate("buggy, use snippet instead")]]
    inline juce::dsp::ProcessContextReplacing<float> buff_to_context (juce::AudioBuffer<float> &buff)
    {
        auto block = juce::dsp::AudioBlock<float>(buff);
        return{ block };
    }
}