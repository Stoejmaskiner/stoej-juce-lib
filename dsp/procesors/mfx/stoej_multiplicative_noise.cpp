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

    this->noise_buffer_ = juce::AudioBuffer<ST>(16,0);

}

template <typename ST>
void stoej::MultiplicativeNoise<ST>::prepare(juce::dsp::ProcessSpec& spec) {

    _sampleRate = spec.sampleRate;
    this->noise_buffer_.setSize(spec.numChannels, spec.maximumBlockSize);
    this->noise_generator_.prepare(spec);
    this->reset();
}

template <typename ST>
void stoej::MultiplicativeNoise<ST>::reset() {

    if (_sampleRate <= 0.f) return;

    // ... your code here ...

    this->noise_generator_.reset();

    _exampleParam.reset(_sampleRate, 0.02);
    _exampleParam.setTargetValue(ST(0.0f));
}


// ========================================================================
template<typename ST>
void stoej::MultiplicativeNoise<ST>::setExampleParam(ST val)
{
    _exampleParam.setTargetValue(val);
}

template<typename ST>
ST stoej::MultiplicativeNoise<ST>::getExampleParam()
{
    return _exampleParam.getTargetValue();
}


// these are the two allowed types
template class stoej::MultiplicativeNoise<float>;
template class stoej::MultiplicativeNoise<double>;