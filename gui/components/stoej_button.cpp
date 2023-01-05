/*
  ==============================================================================

    stoej_button.cpp
    Created: 4 Oct 2022 9:04:08pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_button.h"

#include "binary_data/stoej_Fonts.h"





stoej::StoejButton::StoejButton(const juce::String& name, ButtonSize size, const juce::String& label, bool toggleable)
	: StoejButton(name, size, label, "", nullptr, nullptr, toggleable, false, false) {}

stoej::StoejButton::StoejButton(const juce::String& name, ButtonSize size, const juce::String& label_on, juce::String& label_off)
	: StoejButton(name, size, label_on, label_off, nullptr, nullptr, true, true, false) {}

stoej::StoejButton::StoejButton(const juce::String& name, ButtonSize size, std::unique_ptr<juce::Drawable> icon, bool toggleable)
	: StoejButton(name, size, "", "", std::move(icon), nullptr, toggleable, false, true) {}

stoej::StoejButton::StoejButton(const juce::String& name, ButtonSize size, std::unique_ptr<juce::Drawable> icon_on, std::unique_ptr<juce::Drawable> icon_off)
	: StoejButton(name, size, "", "", std::move(icon_on), std::move(icon_off), true, true, true) {}


stoej::StoejButton::StoejButton(
	const juce::String& name,
	ButtonSize size,
	const juce::String& label_on,
	const juce::String& label_off,
	std::unique_ptr<juce::Drawable> icon_on,
	std::unique_ptr<juce::Drawable> icon_off,
	bool toggleable,
	bool separate_on_off_looks,
	bool use_icon)
	:
	stoej::FloatComponent<juce::Button>(name),
	btn_size_(size),
	label_on_(label_on),
	label_off_(label_off),
	icon_on_(std::move(icon_on)),
	icon_off_(std::move(icon_off)),
	separate_on_off_looks_(separate_on_off_looks),
	use_icon_(use_icon)
{
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
	case tiny:
		return { 24.0f };
	case small:
		return { 36.0f };
	case medium:
		return { 48.0f };
	case large:
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

	if (!this->use_icon_) {
		if (this->getToggleState()) g.setColour(juce::Colours::white);
		else g.setColour(juce::Colours::black);
		g.setFont(stoej::get_font_archivo_narrow());
		g.setFont(13.0 * dp_ * stoej::PT_2_PX);
		g.drawText(this->label_on_, r, juce::Justification::centred);   // draw some placeholder text
	}
	else {
		jassertfalse;	// TODO
	}

	this->setBorderWidth(1.0f);
	this->drawBorder(g);


	
	
	
}

void stoej::StoejButton::paintOn()
{
}

void stoej::StoejButton::paintOff()
{
}







