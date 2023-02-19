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

			// compute wet buffer
			// TODO: there's no way this terrible boilerplate can't be reduced
			auto noise_block = juce::dsp::AudioBlock<ST>(this->work_buffer_);
			auto noise_context = juce::dsp::ProcessContextReplacing<ST>(noise_block);
			this->noise_generator_.process(noise_context);
	        for (size_t c = 0; c < numChans; c++) {
				auto* noise_buff = noise_block.getChannelPointer(c);
				auto* src_in = inBlock.getChannelPointer(c);
	            for (size_t i = 0; i < len; i++) {
	                // computes density transformation on noise as well as gain compensation
					// for very low density having a very low RMS level.
					// gain compensation is non-linear because
					// RMS drops suddenly only for very low density.
					float t = ST(1.0) - this->noise_density_;
					float t_1 = t   * t;
					float t_2 = t_1 * t_1;
					float t_3 = t_2 * t_2; //t^8
					float x = noise_buff[i];
					float gain_compensate = ST(this->DENSITY_GAIN_COMP_) * t_3 + ST(1.0) * (ST(1.0) - t_3);
					float noise_samp = x < t ? (-t < x ? ST(0.0) : x ) : x;
					float in_samp = src_in[i];

					// grit adds additional non-linearity
					if (this->grit_enable_)
					{
						in_samp = stoej::clamp_min(in_samp, ST(0.0));
					}
					// low density noise gets very spiky, so safety clipping to avoid extreme values
					noise_buff[i] = stoej::safety_clip_3db(noise_samp * gain_compensate * in_samp);
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

			// need to do 1 - mix because the xfade function has the destination as the first
			// crossfade argument and we can't write to the input buffer (dry)
			for (size_t c = 0; c < numChans; c++) {
				auto* wet = noise_block.getChannelPointer(c);
				auto* dry = inBlock.getChannelPointer(c);
				auto* dst = outBlock.getChannelPointer(c);
				for (size_t i = 0; i < len; i++) {
					auto coeffs = stoej::xfade_6db_coeffs<ST>(this->noise_mix_.getNextValue());
					dst[i] = stoej::xfade(dry[i], wet[i], coeffs);
				}
			}

			{
				auto* gain_buff = this->work_buffer_.getWritePointer(0);
				for (size_t i = 0; i < len; i++) {
					gain_buff[i] = this->out_level_.getNextValue();
				}
			}
			
			auto* gain_buff = this->work_buffer_.getReadPointer(0);
			for (size_t c = 0; c < numChans; c++) {
				auto* buff = outBlock.getChannelPointer(c);
				juce::FloatVectorOperationsBase<ST,int>::multiply(buff, gain_buff, len);
			}
	    }

	    // ========================================================================
	    void setNoiseWidth(ST val)      {        this->noise_generator_.setNoiseWidth(val); }
	    ST getNoiseWidth()              { return this->noise_generator_.getNoiseWidth(); }
		void setNoiseDensity(ST val)    {        this->noise_density_ = val; }
		ST getNoiseDensity()            { return this->noise_density_; }
		void setNoiseMix(ST val) { this->noise_mix_.setTargetValue(val); }
		ST getNoiseMix() { return this->noise_mix_.getTargetValue(); }
		void setFilterLPCutoff(ST val)  {        this->filter_lp_cutoff_.setTargetValue(val); }
		ST getFilterLPCutoff()          { return this->filter_lp_cutoff_.getTargetValue(); }
		void setFilterHPCutoff(ST val)  {	 	 this->filter_hp_cutoff_.setTargetValue(val); }
		ST getFilterHPCutoff()		    { return this->filter_hp_cutoff_.getTargetValue(); }
		void setGritEnable(bool enable) {		 this->grit_enable_ = enable; }
		bool getGritEnable()		    { return this->grit_enable_; }
		void setOutLevel(ST val) { this->out_level_.setTargetValue(val); }
		ST getOutLevel()				{ return this->out_level_.getTargetValue(); }

	private:

		// ===============================================================
		// adjust these to calibrate
		static constexpr ST DENSITY_GAIN_COMP_ = ST(3.0);	// gain compensation for low density noise

		// ===============================================================
		juce::SmoothedValue<ST> filter_lp_cutoff_;
		juce::SmoothedValue<ST> filter_hp_cutoff_;
		bool grit_enable_ = true;
		ST noise_density_ = ST(1.0);
		//ST noise_mix_ = ST(0.5);
		//ST out_level_ = ST(1.0);
		juce::SmoothedValue<ST> noise_mix_;
		juce::SmoothedValue<ST> out_level_;

		
		juce::AudioBuffer<ST> work_buffer_;
		juce::dsp::StateVariableTPTFilter<ST> filter_lp_;
		juce::dsp::StateVariableTPTFilter<ST> filter_hp_;

	    float sample_rate_ = 48000.f;

	    stoej::WhiteNoise<ST> noise_generator_;
	};
}