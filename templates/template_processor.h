/*
  ==============================================================================

    MultiplicativeNoise.h
    Created: 18 Aug 2022 11:44:36pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

template <typename ST>
class MultiplicativeNoise {
public:
    MultiplicativeNoise();

    void prepare(juce::dsp::ProcessSpec& spec);

    void reset();

    // must be in header to maximize chance of good optimization
    template <typename ProcessContext>
    void process(const ProcessContext& context) noexcept {

        auto&& inBlock  = context.getInputBlock();
        auto&& outBlock = context.getOutputBlock();

        jassert(inBlock.getNumChannels() == outBlock.getNumChannels());
        jassert(inBlock.getNumSamples() == outBlock.getNumSamples());

        auto len = inBlock.getNumSamples();
        auto numChans = inBlock.getNumChannels();

        if (context.isBypassed) {
            this->_exampleParam.skip(static_cast<int> (len));

            if (context.usesSeparateInputAndOutputBlocks())
                outBlock.copyFrom(inBlock);

            return;
        }

        // ... your code here ...

        // example code 1: gain with no explicit vectorization
        /*
        auto* gains = static_cast<ST*>( alloca( sizeof(ST) * len ) );

        for (size_t i = 0; i < len; i++) {
            gains[i] = gain.getNextValue();
        }

        for (size_t c = 0; c < numChans; c++) {
            auto* src = inBlock.getChannelPointer (c);
            auto* dst = outBlock.getChannelPointer (c);
            for (size_t i = 0; i < len; i++) {
                dst[i] = src[i] * gains[i];
            }
        }
        */

        // example code 2: gain with explicit vectorization
        /*
        auto* gains = static_cast<ST*>( alloca( sizeof(ST) * len ) );

        for (size_t i = 0; i < len; i++) {
            gains[i] = gain.getNextValue();
        }

        for (size_t c = 0; c < numChans; c++) {
            auto* src = inBlock.getChannelPointer (c);
            auto* dst = outBlock.getChannelPointer (c);
            juce::FloatVectorOperations::multiply(dst, src, gains, static_cast<int>(len));
        }
        */

        // example code 3: defer to processSample (no opt)
        /*
        
        for (size_t c = 0; c < numChans; c++) {
            auto* src = inBlock.getChannelPointer (c);
            auto* dst = outBlock.getChannelPointer (c);
            for (size_t i = 0; i < len; i++) {
                dst[i] = this->processSample(c, src[i]);
            }
        }
        */

    }

    /// processes a single sample instead of a buffer
    ST processSample(int channel, ST inputValue);

    // ========================================================================
    void setExampleParam(ST val);
    ST getExampleParam();

private:
    juce::SmoothedValue<ST> _exampleParam;
    
    float _sampleRate = 48000.f;
};

