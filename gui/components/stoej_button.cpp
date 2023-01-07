/*
  ==============================================================================

    stoej_button.cpp
    Created: 4 Oct 2022 9:04:08pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_button.h"

#include "binary_data/stoej_Fonts.h"


stoej::StoejButton::StoejButton(
	const juce::String name,
	ButtonSize size,
	const juce::String label_on,
	const juce::String label_off,
	const std::unique_ptr<juce::Drawable>& icon_on,
	const std::unique_ptr<juce::Drawable>& icon_off,
	bool toggleable,
	bool separate_on_off_looks,
	bool use_icon)
	:
	stoej::FloatComponent<juce::Button>(name),
	btn_size_(size),
	label_on_(label_on),
	label_off_(label_off),
	icon_on_(icon_on),
	icon_off_(icon_off),
	separate_on_off_looks_(separate_on_off_looks),
	use_icon_(use_icon)
{
	this->setClickingTogglesState(toggleable);
	this->setToggleable(toggleable);
	this->border_w_ = 1.0f;
	this->border_c_ = juce::Colours::black;
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
	bool pressed = this->isToggleable() && this->getToggleState() || !this->isToggleable() && shouldDrawButtonAsDown;

	if (this->separate_on_off_looks_)
		if (this->use_icon_) this->paintTwoIcons(g, pressed);
		else this->paintTwoLabels(g, pressed);
	else
		if (this->use_icon_) this->paintOneIcon(g, pressed);
		else this->paintOneLabel(g, pressed);
	
	/*
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
		this->icon_on_->drawWithin(g, this->icon_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
	}

	this->setBorderWidth(1.0f);
	this->drawBorder(g);


	
	
	*/
}

void stoej::StoejButton::paintOneIcon(juce::Graphics& g, bool pressed)
{
	auto r = this->getLocalFloatBounds();
	if (pressed) {
		this->background_c_ = juce::Colours::black;
		this->drawBackground(g);
		g.setColour(juce::Colours::white);
		r.reduce(3 * dp_, 3 * dp_);
		this->icon_on_->setBounds(r.toNearestInt());
		// TODO: how to change the colour of this icon???
		this->icon_on_->drawWithin(g, this->icon_on_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
	}
	else {
		this->background_c_ = juce::Colours::white;
		this->drawBackground(g);
		g.setColour(juce::Colours::black);
		r.reduce(3 * dp_, 3 * dp_);
		this->icon_on_->setBounds(r.toNearestInt());
		this->icon_on_->drawWithin(g, this->icon_on_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
	}
	this->drawBorder(g);
}

void stoej::StoejButton::paintTwoIcons(juce::Graphics& g, bool pressed)
{
	// TODO:
	jassertfalse;
}

void stoej::StoejButton::paintOneLabel(juce::Graphics& g, bool pressed)
{
	if (pressed) {
		this->background_c_ = juce::Colours::black;
		this->drawBackground(g);
		this->paintLabel(g, this->label_on_, juce::Colours::white);
	}
	else {
		this->background_c_ = juce::Colours::white;
		this->drawBackground(g);
		this->paintLabel(g, this->label_on_, juce::Colours::black);
	}
	this->drawBorder(g);
}

void stoej::StoejButton::paintTwoLabels(juce::Graphics& g, bool pressed)
{
	// TODO:
	jassertfalse;
}

void stoej::StoejButton::paintLabel(juce::Graphics& g, juce::String label, juce::Colour c) {
	auto r = this->getLocalFloatBounds();
	g.setColour(c);
	g.setFont(stoej::get_font_archivo_narrow());
	g.setFont(13.0f * dp_ * stoej::PT_2_PX);
	g.drawText(label, r, juce::Justification::centred);
}









