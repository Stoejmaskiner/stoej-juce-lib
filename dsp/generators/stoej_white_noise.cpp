/*
  ==============================================================================

    white_noise.cpp
    Created: 21 Aug 2022 2:45:52pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_white_noise.h"

namespace stoej {
    template <typename ST>
    WhiteNoise<ST>::WhiteNoise() {
        this->random_.setSeedRandomly();
        this->initial_seed_ = this->random_.getSeed();
        this->max_size_ = 0;
    }

    template <typename ST>
    WhiteNoise<ST>::WhiteNoise(const juce::int64 seed) {
        this->random_.setSeed(seed);
        this->initial_seed_ = seed;
        this->max_size_ = 0;
    }

    template <typename ST>
    void WhiteNoise<ST>::prepare(juce::dsp::ProcessSpec& spec) {
        this->max_size_ = spec.maximumBlockSize;
        this->reset();
    }

    template <typename ST>
    void WhiteNoise<ST>::reset() {
        this->random_.setSeed(this->initial_seed_);
    }

    // these are the two allowed types
    template class WhiteNoise<float>;
    template class WhiteNoise<double>;
}