/*
  ==============================================================================

    stoej_juce_utils.hpp
    Created: 31 Jul 2022 2:33:41am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace stoej {

    /// alias for juce::AudioParameterFloat smart pointer to be used
    /// in APVTS parameter layout to reduce boilerplate
    auto UniqueParamFloat(auto... args) { 
        return std::make_unique<juce::AudioParameterFloat>(args...); 
    }

    /// alias for juce::AudioParameterBool smart pointer to be used
    /// in APVTS parameter layout to reduce boilerplate
    auto UniqueParamBool(auto... args) {
        return std::make_unique<juce::AudioParameterBool>(args...);
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