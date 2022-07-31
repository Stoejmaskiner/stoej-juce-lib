/*
  ==============================================================================

    stoej_filters.h
    Created: 1 Aug 2022 12:21:23am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace stoej {
   
    class LP1 : juce::dsp::ProcessorBase {
    public:

        /// <summary>
        /// set cutoff with no smoothing once per buffer
        /// </summary>
        /// <param name="cut"></param>
        void set_cutoff(float cut) {

        }
        
        /// <summary>
        /// set cutoff to smoothed buffer
        /// </summary>
        /// <param name="cut"></param>
        void set_cutoff(float* cut_buffer) {

        }
        
        void prepare(const juce::dsp::ProcessSpec& spec) override {

        }

        void process(const juce::dsp::ProcessContextReplacing<float>& context) override {

        }

        void reset() override {}

    private:
        float s1 = 0.0f;
    };
}