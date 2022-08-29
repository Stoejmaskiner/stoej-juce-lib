/*
  ==============================================================================

    TemplateProcessor.cpp
    Created: 18 Aug 2022 11:44:36pm
    Author:  Lorenzo

    This template is based on standard practices found in the official 
    juce::dsp widgets

  ==============================================================================
*/

#include "template_processor.h"

template <typename ST>
TemplateProcessor<ST>::TemplateProcessor() {
    
    // ... your code here ...

}

template <typename ST>
void TemplateProcessor<ST>::prepare(juce::dsp::ProcessSpec& spec) {

    _sampleRate = spec.sampleRate;
    this->reset();
}

template <typename ST>
void TemplateProcessor<ST>::reset() {

    if (_sampleRate <= 0.f) return;

    // ... your code here ...

    _exampleParam.reset(_sampleRate, 0.02);
    _exampleParam.setTargetValue(ST(0.0f));
}

template<typename ST>
ST TemplateProcessor<ST>::processSample(int channel, ST inputValue)
{
    // ... your code here ...

    // NOTE: this is how you advance the smoothed params
    ST _exampleVal = _exampleParam.getNextValue();
    return ST(0.0f); // <-- comment this out
}


// ========================================================================
template<typename ST>
void TemplateProcessor<ST>::setExampleParam(ST val)
{
    _exampleParam.setTargetValue(val);
}

template<typename ST>
ST TemplateProcessor<ST>::getExampleParam()
{
    return _exampleParam.getTargetValue();
}


// these are the two allowed types
template class TemplateProcessor<float>;
template class TemplateProcessor<double>;