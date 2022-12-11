/*
  ==============================================================================

    stoej_button.cpp
    Created: 4 Oct 2022 9:04:08pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_button.h"




stoej::StoejButton::StoejButton(const juce::String& button_name, ButtonVariant b_var, ButtonSize b_size, bool toggleable = false) : juce::Button(button_name), btn_variant_(b_var), btn_size_(b_size) {
	this->setClickingTogglesState(toggleable);
	this->setToggleable(true);
	this->addAndMakeVisible(this->bounding_box_);
	this->bounding_box_.setInterceptsMouseClicks(false, false);
}

std::variant<int, stoej::DynamicSize> stoej::StoejButton::getHeight()
{
    return {24};
}

std::variant<int, stoej::DynamicSize> stoej::StoejButton::getWidth()
{
    // TODO: performance tuning with constexpr if and templates?
    switch (this->btn_variant_) {
    case e_text: 
		switch (this->btn_size_) {
		case e_tiny:
			return {24};
		case e_small:
			return {36};
		case e_medium:
			return {48};
		case e_large:
			return {60};
		default: 
			return {48};
		}
	case e_icon: return {24};
    default: return {48};
    }
}

void stoej::StoejButton::setDP(double dp)
{
	this->dp_ = dp;
	this->bounding_box_.setDP(dp);
}

void stoej::StoejButton::setTilePosition(TilePosition pos)
{
	this->tile_position_ = pos;
	this->bounding_box_.setTilePosition(pos);
}

void stoej::StoejButton::resized()
{
    auto r = getLocalBounds();
	this->bounding_box_.setBounds(r);

}

void stoej::StoejButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto r = getLocalBounds();

	// toggle button drawing logic
	if(this->isToggleable()) {
		if (this->getToggleState()) this->bounding_box_.fill_color = juce::Colours::black;
		else this->bounding_box_.fill_color = juce::Colours::white;
		

    // trigger button drawing logic 
	} else {
		//if (shouldDrawButtonAsDown) g.setColour(juce::Colours::red);
		//if (!shouldDrawButtonAsDown) g.setColour(juce::Colours::black);
		//g.drawRect(r);
	}
	
	
}




