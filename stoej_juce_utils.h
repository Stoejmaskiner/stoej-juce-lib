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

    /// convert juce::AudioBuffer to juce::dsp::ProcessContextReplacing
    /// to reduce boilerplate
    inline juce::dsp::ProcessContextReplacing<float> buff_to_context (juce::AudioBuffer<float> &buff)
    {
        auto block = juce::dsp::AudioBlock<float>(buff);
        return{ block };
    }

    /// convert juce::AudioBuffer<float> to juce::dps::AudioBlock<float>
    /// to reduce boilerplate
    inline juce::dsp::AudioBlock<float> buff_to_block(juce::AudioBuffer<float>& buff)
    {
        return { buff };
    }

    /// copy the contents of one buffer (src) into another (dst)
    inline void buffer_copy (juce::AudioBuffer<float>& src, juce::AudioBuffer<float>& dst)
    {;
        int src_chan = src.getNumChannels();
        int src_size = src.getNumSamples();
        int dst_chan = src.getNumChannels();
        int dst_size = src.getNumSamples();
        jassert(src_chan == dst_chan);
        jassert(src_size == dst_size);

        for(int c = 0; c < src_chan; c++)
        {
            dst.copyFrom(c, 0, src, c, 0, src_size);
        }
    }

}