/*
  ==============================================================================

    Box.h
    Created: 1 Sep 2022 12:13:15pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "gui/interfaces/stoej_component.h"

//==============================================================================
/*
*/

namespace stoej {
	class Box : public juce::Component, public stoej::IResizableComponent
	{

	public:
		juce::Colour stroke_color = juce::Colour(  0,   0,   0);
		juce::Colour fill_color   = juce::Colour(255, 255, 255);

		Box() = default;
		~Box() override = default;
		

	    void paint (juce::Graphics& g) override {
	        auto r = getLocalBounds();

	        g.setColour(this->fill_color);
	        g.fillAll();
	        g.setColour(this->stroke_color);
	        g.drawRect(r);
	    }

	    std::variant<int, stoej::DynamicSize> getPreferredHeight() override {
		    return stoej::DynamicSize::e_parent_decides;
	    }

	    std::variant<int, stoej::DynamicSize> getPreferredWidth() override {
		    return stoej::DynamicSize::e_parent_decides;
	    }

	    void setDP(double dp) override {}

	private:
	    
	    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Box)
	};
}