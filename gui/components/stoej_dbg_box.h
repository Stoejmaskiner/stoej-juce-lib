/*
  ==============================================================================

    stoej_dbg_box_.h
    Created: 1 Sep 2022 4:29:12pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
namespace stoej {
	class DbgBox  : public juce::Component
	{
	public:
	    DbgBox() = default;
	    ~DbgBox() override = default;

	    void paint (juce::Graphics& g) override
	    {
	        const auto rand = static_cast<juce::uint64>(this->random_.nextInt64());
	        const juce::uint8 r_val = (rand >> 8)  & 0xFF;
	        const juce::uint8 g_val = (rand >> 16) & 0xFF;
	        const juce::uint8 b_val = (rand >> 24) & 0xFF;
	        g.setColour (juce::Colour(r_val, g_val, b_val));
	        g.drawRect (getLocalBounds(), 2);   // draw an outline around the component
	    }

	private:
	    juce::Random random_;
	    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DbgBox)
	};
}