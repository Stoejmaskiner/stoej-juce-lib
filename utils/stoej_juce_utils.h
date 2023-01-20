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

    // TODO: move params to stoej_params.h

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