/*
  ==============================================================================

    stoej_random.hpp
    Created: 29 Jul 2022 5:38:02pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace stoej {

	/**
	 * \brief fills buffer with bipolar white noise at unity gain
	 */
	class WhiteNoise : juce::dsp::ProcessorBase
    {
    public:
        WhiteNoise() : ProcessorBase() {
            this->random_.setSeedRandomly();
            this->initial_seed_ = this->random_.getSeed();
        }

        WhiteNoise(const juce::int64 seed) : ProcessorBase()
        {
            this->random_.setSeed(seed);
            this->initial_seed_ = seed;
        }

        void prepare(const juce::dsp::ProcessSpec&) override {};

        void process(const juce::dsp::ProcessContextReplacing<float>& context) override
        {
            // ===== getting stuff =====
            const auto block = context.getOutputBlock();
            const auto num_chans = block.getNumChannels();
            const auto size = context.getOutputBlock().getNumSamples();

            for (juce::uint32 c = 0; c < num_chans; c++)
            {
                const auto sink_ptr = block.getChannelPointer(c);
                for (juce::uint32 i = 0; i < size; i++)
                {
                    sink_ptr[i] = this->random_.nextFloat() * 2.0f - 1.0f;
                }
            }
        }

        void reset() override
        {
            this->random_.setSeed(this->initial_seed_);
        }

    private:
        juce::int64 initial_seed_;
        juce::Random random_;
    };
}