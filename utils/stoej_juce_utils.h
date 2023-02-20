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
#include "stoej_params.h"

namespace stoej {

    

    /// convert juce::AudioBuffer to juce::dsp::ProcessContextReplacing
    /// to reduce boilerplate
    [[deprecated("buggy, use snippet instead")]]
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

    // TODO: these should be part of a custom apvts class

    // reset an APVTS parameter
    inline void apvts_reset_param(juce::AudioProcessorValueTreeState& apvts, juce::StringRef id) {
        auto p = apvts.getParameter(id);
        auto def = p->getDefaultValue();
        p->setValueNotifyingHost(def);
    }

    // randomize an APVTS parameter
    inline void apvts_random_param(juce::AudioProcessorValueTreeState& apvts, juce::StringRef id) {
        auto p = apvts.getParameter(id);
        auto val = juce::Random::getSystemRandom().nextFloat();
        p->setValueNotifyingHost(val);
    }

    // mutate an APVTS parameter
    // TODO: inline void apvts_mutate_param()

}