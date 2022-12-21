/*
  ==============================================================================

    stoej_button.cpp
    Created: 4 Oct 2022 9:04:08pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_button.h"




stoej::StoejButton::StoejButton(
			const juce::String& button_name, 
			ButtonVariant b_var, 
			ButtonSize b_size, 
			bool toggleable) : 
		btn_variant_(b_var), 
		btn_size_(b_size), 
		stoej::FloatComponent<juce::Button>(button_name),
		icon_(nullptr),
		label_((char*) nullptr),
		font_(juce::Font()) {
	this->setClickingTogglesState(toggleable);
	this->setToggleable(toggleable);
}

stoej::StoejButton::StoejButton(
			const juce::String& button_name,
			ButtonSize b_size,
			const std::unique_ptr<juce::Drawable>& icon,
			bool toggleable) : 
		btn_variant_(ButtonVariant::e_icon),
		btn_size_(b_size),
		stoej::FloatComponent<juce::Button>(button_name),
		icon_(icon),
		label_((char*) nullptr),
		font_(juce::Font()) {
	this->setClickingTogglesState(toggleable);
	this->setToggleable(toggleable);
}

stoej::StoejButton::StoejButton(
			const juce::String& button_name,
			ButtonSize b_size,
			const char* label,
			const juce::Font& font,
			bool toggleable) :
		btn_variant_(ButtonVariant::e_text),
		btn_size_(b_size),
		stoej::FloatComponent<juce::Button>(button_name),
		icon_(nullptr),
		label_(label),
		font_(font) {
	this->setClickingTogglesState(toggleable);
	this->setToggleable(toggleable);
}

std::variant<float, stoej::DynamicSize2> stoej::StoejButton::getPreferredHeight()
{
    return {24.0f};
}

std::variant<float, stoej::DynamicSize2> stoej::StoejButton::getPreferredWidth()
{
    // TODO: performance tuning with constexpr if and templates?
	switch (this->btn_size_) {
	case e_tiny:
		return { 24.0f };
	case e_small:
		return { 36.0f };
	case e_medium:
		return { 48.0f };
	case e_large:
		return { 60.0f };
	default:
		jassertfalse;
	}
}


void stoej::StoejButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	auto r = getLocalFloatBounds();
	//this->setBorderWidth(1.0f);
	//this->drawBorder(g);

	//if (shouldDrawButtonAsDown) jassertfalse;
	//if (shouldDrawButtonAsHighlighted) jassertfalse;

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


	this->drawBackground(g);

	switch (this->btn_variant_) {
	case e_text:
		if (this->getToggleState()) g.setColour(juce::Colours::white);
		else g.setColour(juce::Colours::black);
		g.setFont(this->font_);
		g.setFont(13.0 * dp_ * stoej::PT_2_PX);
		g.drawText(this->label_, r, juce::Justification::centred);   // draw some placeholder text
		break;
	case e_icon:
		break;
	}

	this->setBorderWidth(1.0f);
	this->drawBorder(g);
	
	
	
}




