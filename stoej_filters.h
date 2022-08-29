/*
  ==============================================================================

    stoej_filters.h
    Created: 1 Aug 2022 12:21:23am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "stoej_base.h"
#include <cmath>

// TODO: untested
// NOTE 1: this is useless because it's already implemented in juce::dsp
namespace stoej {

    inline float cutoff_normalize(float freq, float sr) { return freq / sr * stoej::TAU; }

    inline float coeff_1p(float freq, float sr) {
        const float wc = cutoff_normalize(freq, sr);
        return -std::exp(-wc);
    }
   
    class LP1 : juce::dsp::ProcessorBase {
    public:
        BufferedParameter cutoff;

        LP1() : juce::dsp::ProcessorBase() {
            this->max_size_ = 0;
            this->sample_rate_ = 0.0f;
            this->state_vector_ = juce::AudioBuffer<float>(16, 1);
        }
        
        void prepare(const juce::dsp::ProcessSpec& spec) override {
            this->max_size_ = spec.maximumBlockSize;
            this->sample_rate_ = spec.sampleRate;
            this->cutoff.prepare(spec);
        }

        void process(const juce::dsp::ProcessContextReplacing<float>& context) override {
            auto block = context.getOutputBlock();
            auto size = block.getNumSamples();
            auto num_chans = block.getNumChannels();
            
            for (size_t i = 0; i < this->max_size_ && i < size; i++)
            {
                float b1 = stoej::coeff_1p(this->cutoff.get_at(i), this->max_size_);
                float a0 = 1.0f - b1;
                for (size_t c = 0; c < num_chans; c++) {
                    float* buffer = block.getChannelPointer(c);
                    float* state = this->state_vector_.getWritePointer(c);
                    *state = buffer[i] * a0 + (*state) * b1;
                    buffer[i] = *state;
                }
            }
        }

        void reset() override {}

    private:
        juce::AudioBuffer<float> state_vector_;
        BufferedParameter cutoff_;
        size_t max_size_;
        float sample_rate_;
    };
}