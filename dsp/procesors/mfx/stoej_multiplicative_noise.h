/*
  ==============================================================================

    stoej_multiplicative_noise.h
    Created: 29 Aug 2022 8:34:02pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "dsp/generators/stoej_white_noise.h"
#include "utils/stoej_nonlinearities.h"
#include "utils/stoej_xfade.h"


namespace stoej {
	template <typename ST>
	class MultiplicativeNoise {
	public:
	    MultiplicativeNoise();
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

			// bypass processor
	        if (context.isBypassed) {
				this->filter_lp_cutoff_.skip(static_cast<int> (len));
				this->filter_hp_cutoff_.skip(static_cast<int> (len));
	            if (context.usesSeparateInputAndOutputBlocks())
	                outBlock.copyFrom(inBlock);
	            return;
	        }

			auto noise_block = juce::dsp::AudioBlock<ST>(this->noise_buffer_);
			auto noise_context = juce::dsp::ProcessContextReplacing<ST>(noise_block);
			this->noise_generator_.process(noise_context);

			// compute wet buffer
	        for (size_t c = 0; c < numChans; c++) {
				auto* noise_buff = noise_block.getChannelPointer(c);
				auto* src_in = inBlock.getChannelPointer(c);
	            for (size_t i = 0; i < len; i++) {
	                float noise_samp = stoej::symmetric_pow(noise_buff[i], ST(1.0) / (ST(0.00002) + this->noise_density_));
					noise_buff[i] = noise_samp * src_in[i];
	            }
	        }

			for (size_t c = 0; c < numChans; c++) {
				auto* noise_buff = noise_block.getChannelPointer(c);
				for (size_t i = 0; i < len; i++) {
					auto lp_cut = this->filter_lp_cutoff_.getNextValue();
					auto hp_cut = this->filter_hp_cutoff_.getNextValue();
					this->filter_lp_.setCutoffFrequency(lp_cut);
					this->filter_hp_.setCutoffFrequency(hp_cut);
					noise_buff[i] = this->filter_lp_.processSample(c, noise_buff[i]);
					noise_buff[i] = this->filter_hp_.processSample(c, noise_buff[i]);
				}
			}

			// crossfade
			auto coeffs = stoej::xfade_fast_transition(this->noise_mix_);
			// need to do 1 - mix because the xfade function has the destination as the first
			// crossfade argument and we can't write to the input buffer (dry)
			for (size_t c = 0; c < numChans; c++) {
				auto* wet = noise_block.getChannelPointer(c);
				auto* dry = inBlock.getChannelPointer(c);
				auto* dst = outBlock.getChannelPointer(c);
				stoej::xfade<ST>(dst, dry, wet, coeffs, len);
			}

			for (size_t c = 0; c < numChans; c++) {
				auto* buff = outBlock.getChannelPointer(c);
				juce::FloatVectorOperationsBase<ST,int>::multiply(buff, this->getOutLevel(), len);
			}
			
		


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

	    // ========================================================================
	    void setNoiseWidth(ST val)      {        this->noise_generator_.setNoiseWidth(val); }
	    ST getNoiseWidth()              { return this->noise_generator_.getNoiseWidth(); }
		void setNoiseDensity(ST val)    {        this->noise_density_ = val; }
		ST getNoiseDensity()            { return this->noise_density_; }
		void setNoiseMix(ST val)        {        this->noise_mix_ = val; }
		ST getNoiseMix()                { return this->noise_mix_; }
		void setFilterLPCutoff(ST val)  {        this->filter_lp_cutoff_.setTargetValue(val); }
		ST getFilterLPCutoff()          { return this->filter_lp_cutoff_.getTargetValue(); }
		void setFilterHPCutoff(ST val)  {	 	 this->filter_hp_cutoff_.setTargetValue(val); }
		ST getFilterHPCutoff()		    { return this->filter_hp_cutoff_.getTargetValue(); }
		void setGritEnable(bool enable) {		 this->grit_enable_ = enable; }
		bool getGritEnable()		    { return this->grit_enable_; }
		void setOutLevel(ST val)		{		 this->out_level_ = val; }
		ST getOutLevel()				{ return this->out_level_; }

	private:
		juce::SmoothedValue<ST> filter_lp_cutoff_;
		juce::SmoothedValue<ST> filter_hp_cutoff_;
		bool grit_enable_;
		ST noise_density_ = ST(1.0);
		ST noise_mix_ = ST(0.5);
		ST out_level_ = ST(1.0);

		
		juce::AudioBuffer<ST> noise_buffer_;
		juce::dsp::StateVariableTPTFilter<ST> filter_lp_;
		juce::dsp::StateVariableTPTFilter<ST> filter_hp_;

	    float sample_rate_ = 48000.f;

	    stoej::WhiteNoise<ST> noise_generator_;
	};
}