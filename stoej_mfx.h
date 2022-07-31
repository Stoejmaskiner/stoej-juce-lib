/*
  ==============================================================================

    stoej_mfx.hpp
    Created: 31 Jul 2022 2:14:04am
    Author:  Lorenzo
    Description:
    MFX are micro-effects, in other words they are minimalistic ready made effect
    modules to be used as part of a larger project.

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "stoej_random.h"
#include "stoej_juce_utils.h"

namespace stoej {
    class RingModNoise : juce::dsp::ProcessorBase {
    public:
        RingModNoise() : juce::dsp::ProcessorBase() {}
        RingModNoise(juce::int64 seed) : juce::dsp::ProcessorBase()
        {
            this->noise_ = stoej::WhiteNoise(seed);
        }
        void prepare(const juce::dsp::ProcessSpec&) override {}
        void process(const juce::dsp::ProcessContextReplacing<float>& context) override
        {
            const auto block = context.getOutputBlock();
            const auto num_chans = block.getNumChannels();
            const auto size = block.getNumSamples();

            auto noise_buff = juce::AudioBuffer<float>(num_chans, size);
            noise_buff.clear();
            this->noise_.process(stoej::buff_to_context(noise_buff));

            for (size_t c = 0; c < num_chans; c++)
            {
                auto in_chan = block.getChannelPointer(c);
                auto noise_chan = noise_buff.getWritePointer(c);
	            for (size_t i = 0; i < size; i++)
	            {
                    in_chan[i] *= noise_chan[i];
	            }
            }
        }
        void reset() override;
    private:
        stoej::WhiteNoise noise_;
    };

    class RingModDust : juce::dsp::ProcessorBase {
        // TODO
    };
}