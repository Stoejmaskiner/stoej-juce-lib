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
#include "stoej_juce_utils.h"
#include "stoej_math.h"
#include <valarray>

// TODO: consider if parameter smoothing is necessary
namespace stoej {
    class RingModNoiseA : juce::dsp::ProcessorBase {
    public:
        float noise_width = 0.5f;

        RingModNoiseA() : juce::dsp::ProcessorBase() {
            this->max_size = 0;
            this->sample_rate = 0.0f;
            this->mono_noise = juce::AudioBuffer<float>(0,0);
        }
        RingModNoiseA(juce::int64 seed) : juce::dsp::ProcessorBase()
        {
            this->max_size = 0;
            this->sample_rate = 0.0f;
            this->random_ = juce::Random(seed);
            this->mono_noise = juce::AudioBuffer<float>(0, 0);
        }
        void prepare(const juce::dsp::ProcessSpec& spec) override {
            this->max_size = spec.maximumBlockSize;
            this->sample_rate = spec.sampleRate;
            this->mono_noise.setSize(1, this->max_size, false, false, true);
        }

        void process(const juce::dsp::ProcessContextReplacing<float>& context) override
        {
            const auto block = context.getOutputBlock();
            const auto num_chans = block.getNumChannels();
            const auto size = block.getNumSamples();

            // fill mono nosie buffer
            auto mono_noise_buff = this->mono_noise.getWritePointer(0);
            for (size_t i = 0; i < size && i < this->max_size; i++) {
                mono_noise_buff[i] = this->random_.nextFloat() * 2.0f - 1.0f;
            }

            for (size_t c = 0; c < num_chans; c++)
            {
                auto in_chan = block.getChannelPointer(c);

                // TODO: OPT: attempt optimization with SIMD vectorization e.g. with valarray
	            for (size_t i = 0; i < size && i < this->max_size; i++)
	            {
                    float noise_sample = (this->random_.nextFloat() * 2.0f - 1.0f) * this->noise_width 
                                       + mono_noise_buff[i] * (1.0f - this->noise_width);
                    in_chan[i] *= noise_sample;
	            }
            }
        }
        void reset() override {}
    private:
        size_t max_size;
        float sample_rate;
        juce::Random random_;
        juce::AudioBuffer<float> mono_noise;
    };

    class RingModNoiseB : juce::dsp::ProcessorBase {
    public:
        float noise_width = 0.5f;

        RingModNoiseB() : juce::dsp::ProcessorBase() {
            this->max_size = 0;
            this->sample_rate = 0.0f;
            this->mono_noise = juce::AudioBuffer<float>(0, 0);
        }
        RingModNoiseB(juce::int64 seed) : juce::dsp::ProcessorBase()
        {
            this->max_size = 0;
            this->sample_rate = 0.0f;
            this->random_ = juce::Random(seed);
            this->mono_noise = juce::AudioBuffer<float>(0, 0);
        }
        void prepare(const juce::dsp::ProcessSpec& spec) override {
            this->max_size = spec.maximumBlockSize;
            this->sample_rate = spec.sampleRate;
            this->mono_noise.setSize(1, this->max_size, false, false, true);
        }

        void process(const juce::dsp::ProcessContextReplacing<float>& context) override
        {
            const auto block = context.getOutputBlock();
            const auto num_chans = block.getNumChannels();
            const auto size = block.getNumSamples();

            // fill mono nosie buffer
            auto mono_noise_buff = this->mono_noise.getWritePointer(0);
            for (size_t i = 0; i < size && i < this->max_size; i++) {
                mono_noise_buff[i] = this->random_.nextFloat() * 2.0f - 1.0f;
            }

            for (size_t c = 0; c < num_chans; c++)
            {
                auto in_chan = block.getChannelPointer(c);

                // TODO: OPT: attempt optimization with SIMD vectorization e.g. with valarray
                for (size_t i = 0; i < size && i < this->max_size; i++)
                {
                    float noise_sample = (this->random_.nextFloat() * 2.0f - 1.0f) * this->noise_width
                        + mono_noise_buff[i] * (1.0f - this->noise_width);

                    noise_sample *= noise_sample; // squared
                    noise_sample = stoej::clamp_min(noise_sample, 0.f);

                    in_chan[i] = stoej::clamp_min(in_chan[i], 0.f) * noise_sample;                }
            }
        }
        void reset() override {}
    private:
        size_t max_size;
        float sample_rate;
        juce::Random random_;
        juce::AudioBuffer<float> mono_noise;
    };
}


