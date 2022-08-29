/*
  ==============================================================================

    stoej_base.h
    Created: 31 Jul 2022 5:19:38pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace stoej
{
	constexpr float PI = 3.14159265359f;
	constexpr float TAU = 6.28318530718f;
	constexpr float NEG_PI = -3.14159265359f;
	constexpr float NEG_TAU = -6.28318530718f;

	/// <summary>
	/// A parameter that can either be used as a sporadically set value or as a
	///	continuous buffer for audio-rate modulation.
	/// </summary>
	class BufferedParameter
	{
	public:

		BufferedParameter()
		{
			this->buffered_val_ = juce::AudioBuffer<float>(1, 0);
			this->is_buffered_ = false;
			this->max_size_ = 0;
			this->sample_rate_ = 0;
			this->static_val_ = 0.0f;
		}

		/**
		 * \brief must be called at least once
		 * \param spec 
		 */
		void prepare(const juce::dsp::ProcessSpec& spec)
		{
			this->max_size_ = spec.maximumBlockSize;
			this->sample_rate_ = spec.sampleRate;
			this->buffered_val_.setSize(1, this->max_size_, false, false, true);
		}

		void set(float val)
		{
			this->static_val_ = val;
			this->is_buffered_ = false;
		}

		void set(const juce::AudioBuffer<float>& buffer)
		{
			this->buffered_val_.copyFrom(0, 0, buffer, 0, 0, this->max_size_);
			this->is_buffered_ = true;
		}

		float get_at(size_t idx)
		{
			if (this->is_buffered_) {
				return this->buffered_val_.getReadPointer(0)[idx];
			}
			return this->static_val_;
		}

		// TODO: untested
		const float* get_as_array()
		{
			if (!this->is_buffered_)
			{
				float* buffer_ptr_ = this->buffered_val_.getWritePointer(0);
				for (size_t i = 0; i < this->max_size_; i++)
				{
					buffer_ptr_[i] = this->static_val_;
				}
			}
			return this->buffered_val_.getReadPointer(0);
		}

	private:
		size_t max_size_;
		float sample_rate_;
		float static_val_;
		juce::AudioBuffer<float> buffered_val_;
		bool is_buffered_;
	};


}