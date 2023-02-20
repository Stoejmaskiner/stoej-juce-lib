/*
  ==============================================================================

    white_noise.h
    Created: 21 Aug 2022 2:45:52pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <utils/stoej_xfade.h>


namespace stoej {
    template <typename ST>
    class WhiteNoise {
    public:

        /// initialize with random seed
        WhiteNoise();

        /// initialize with given seed
        WhiteNoise(const juce::int64 seed);

        void prepare(juce::dsp::ProcessSpec& spec);

        void reset();

        // must be in header to maximize chance of good optimization
        template <typename ProcessContext>
        void process(const ProcessContext& context) noexcept {

            auto&& inBlock = context.getInputBlock();
            auto&& outBlock = context.getOutputBlock();

            jassert(inBlock.getNumChannels() == outBlock.getNumChannels());
            jassert(inBlock.getNumSamples() == outBlock.getNumSamples());

            auto len = inBlock.getNumSamples();
            auto numChans = inBlock.getNumChannels();

            if (context.isBypassed) {

                if (context.usesSeparateInputAndOutputBlocks())
                    outBlock.copyFrom(inBlock);

                return;
            }

            // fill mono noise buffer
            // TODO: OPT: consider moving out ot process and realloc only on resize
            auto* mono_noise_buff = static_cast<ST*>( alloca( sizeof(ST) * len ));
            for (size_t i = 0; i < len; i++) {
                mono_noise_buff[i] = this->processSample();
            }

            // fill selection buffer
            bool* selection_buff = nullptr;
            if(this->enable_hq_width_)
            {
                selection_buff = static_cast<bool*>(alloca(sizeof(bool) * len));
                for(size_t i = 0; i < len; i++)
                {
                    selection_buff[i] = this->random_.nextFloat() < this->noise_width_;
                }
            }
            
            

            // fill destination with stereo noise
            for (size_t c = 0; c < numChans; c++) {
                auto* dst = outBlock.getChannelPointer(c);
                for (size_t i = 0; i < len; i++) {
                    dst[i] = this->processSample();
                }
            }

            // mono-stereo crossfade
            auto xfade_coeffs = stoej::fast_xfade_coeffs<ST, -3>(ST(1.) - this->noise_width_);
            for (size_t c = 0; c < numChans; c++) {
	            auto* dst = outBlock.getChannelPointer(c);
                if (this->enable_hq_width_)
                {
                    // expensive width computation
	                for (size_t i = 0; i < len; i++)
	                {
                        dst[i] = selection_buff[i] ? dst[i] : mono_noise_buff[i];
	                }
                } else
                {
                    // cheap width computation
                    stoej::xfade(dst, mono_noise_buff, xfade_coeffs, len);
                }
            }

        }

        /// processes a single sample instead of a buffer, note that
        /// the width parameter does nothing when processing single samples
        /// as it requires multi-channel awareness
        ST processSample() {
            if constexpr (std::is_same_v<ST, float>) {
                return this->random_.nextFloat() * 2.0f - 1.0f;
            }
            return this->random_.nextDouble() * 2.0 - 1.0;
        }

        // ========================================================================
        void setNoiseWidth(ST val) { this->noise_width_ = val; }
        ST getNoiseWidth() { return this->noise_width_; }

        /// Enables more expensive computation of noise width that guarantees uniform
        /// distribution for all intermediate values of noise width.
        ///
        /// Normally, intermediate widths are obtained by power preserving crossfade
        /// of a mono buffer and a stereo buffer. Perceptually, this sounds very
        /// smooth, however the statistical distribution of the noise changes with
        /// the value of width, which would affect any non-linear post processing
        /// done to the noise.
        ///
        /// To counter this, enabling HQ width guarantees that the distribution
        /// will remain uniform for all values of noise_width_, by adding an
        /// additional bernoulli random variable that chooses whether each sample
        /// is taken from the stereo buffer or the mono buffer.
        ///
        /// <b>Caveats</b>\n
        /// While this method is good enough for sound processing it has some
        /// strange undesired statistical side effects, so it should not be used as
        /// for any precise statistical purposes.
        ///
        /// Specifically, the individual samples in one frame are always either fully
        /// correlated or fully uncorrelated, but the probability of them being correlated
        /// or not determines their long-term average correlation.
        ///
        /// Acoustically this has no or very subtle effect, but it might have subtle sub-liminal
        /// or psychoacoustic effects.
        void setEnableHQWidth(bool enable) { this->enable_hq_width_ = enable; }
        ST getEnableHQWidth() { return this->enable_hq_width_; }

    private:
        ST noise_width_ = ST(.5);
        bool enable_hq_width_ = false;
        size_t max_size_;
        juce::int64 initial_seed_;
        juce::Random random_;
    };
}