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
    inline auto UniqueParamFloat(auto... args) { 
        return std::make_unique<juce::AudioParameterFloat>(args...); 
    }

    /// alias for juce::AudioParameterBool smart pointer to be used
    /// in APVTS parameter layout to reduce boilerplate
    inline auto UniqueParamBool(auto... args) {
        return std::make_unique<juce::AudioParameterBool>(args...);
    }
}