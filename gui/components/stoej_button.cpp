/*
  ==============================================================================

    stoej_button.cpp
    Created: 4 Oct 2022 9:04:08pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_button.h"




stoej::StoejButton::StoejButton(const juce::String& button_name, ButtonVariant b_var, ButtonSize b_size, bool toggleable = false) : btn_variant_(b_var), btn_size_(b_size), stoej::FloatComponent<juce::Button>(button_name) {
	this->setClickingTogglesState(toggleable);
	this->setToggleable(true);
	//this->addAndMakeVisible(this->bounding_box_);
	//this->bounding_box_.setInterceptsMouseClicks(false, false);
}

std::variant<float, stoej::DynamicSize2> stoej::StoejButton::getPreferredHeight()
{
    return {24.0f};
}

std::variant<float, stoej::DynamicSize2> stoej::StoejButton::getPreferredWidth()
{
    // TODO: performance tuning with constexpr if and templates?
    switch (this->btn_variant_) {
    case e_text: 
		switch (this->btn_size_) {
		case e_tiny:
			return {24.0f};
		case e_small:
			return {36.0f};
		case e_medium:
			return {48.0f};
		case e_large:
			return {60.0f};
		default: 
			return {48.0f};
		}
	case e_icon: return {24.0f};
    default: return {48.0f};
    }
}


void stoej::StoejButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto r = getLocalFloatBounds();

	// toggle button drawing logic
	if(this->isToggleable()) {
		// TODO(Lorenzo): got here
		if (this->getToggleState()) this->background_c_ = juce::Colours::black; //this->bounding_box_.fill_color = juce::Colours::black;
		else this->background_c_ = juce::Colours::white;
		

    // trigger button drawing logic 
	} else {
		//if (shouldDrawButtonAsDown) g.setColour(juce::Colours::red);
		//if (!shouldDrawButtonAsDown) g.setColour(juce::Colours::black);
		//g.drawRect(r);
	}

	this->setBorderWidth(1.0f);
	this->drawBackground(g);
	this->drawBorder(g);
	
	
	
}




