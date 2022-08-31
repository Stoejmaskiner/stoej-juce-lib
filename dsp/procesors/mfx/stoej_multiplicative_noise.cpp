/*
  ==============================================================================

    stoej_multiplicative_noise.cpp
    Created: 29 Aug 2022 8:34:02pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_multiplicative_noise.h"


template <typename ST>
stoej::MultiplicativeNoise<ST>::MultiplicativeNoise() {

    this->filter_lp_.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
    this->filter_hp_.setType(juce::dsp::StateVariableTPTFilterType::highpass);
    this->noise_generator_.setEnableHQWidth(true);
    this->noise_buffer_ = juce::AudioBuffer<ST>(16,0);

}

template <typename ST>
void stoej::MultiplicativeNoise<ST>::prepare(juce::dsp::ProcessSpec& spec) {

    sample_rate_ = spec.sampleRate;
    this->noise_buffer_.setSize(spec.numChannels, spec.maximumBlockSize);
    this->noise_generator_.prepare(spec);
    this->filter_lp_.prepare(spec);
    this->filter_hp_.prepare(spec);
    this->reset();
}

template <typename ST>
void stoej::MultiplicativeNoise<ST>::reset() {

    if (sample_rate_ <= 0.f) return;

    // ... your code here ...

    this->noise_generator_.reset();
    this->filter_lp_.reset();
    this->filter_hp_.reset();
    this->filter_lp_cutoff_.reset(sample_rate_, 0.02);
    this->filter_hp_cutoff_.reset(sample_rate_, 0.02);
}


// these are the two allowed types
template class stoej::MultiplicativeNoise<float>;
template class stoej::MultiplicativeNoise<double>;