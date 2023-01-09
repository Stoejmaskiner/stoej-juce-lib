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
	bool use_icon)
	:
	stoej::FloatComponent<juce::Button>(name),
	btn_size_(size),
	label_on_(label_on),
	label_off_(label_off),
	icon_on_(icon_on),
	icon_off_(icon_off),
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

void stoej::StoejButton::resized()
{
	auto r = this->getLocalFloatBounds();
	r.reduce(3 * dp_, 3 * dp_);
	this->icon_on_->setBounds(r.toNearestInt());
	this->icon_off_->setBounds(r.toNearestInt());
}


void stoej::StoejButton::paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
	bool pressed = this->isToggleable() && this->getToggleState() || !this->isToggleable() && shouldDrawButtonAsDown;
	if (this->use_icon_) this->paintIcon(g, pressed);
	else this->paintLabel(g, pressed);
}

void stoej::StoejButton::paintLabel(juce::Graphics& g, bool pressed) {
	auto r = this->getLocalFloatBounds();
	if (pressed) {
		this->background_c_ = juce::Colours::black;
		this->drawBackground(g);
		g.setColour(juce::Colours::white);
		g.setFont(stoej::get_font_archivo_narrow());
		g.setFont(13.0f * dp_ * stoej::PT_2_PX);
		g.drawText(this->label_on_, r, juce::Justification::centred);

	}
	else {
		this->background_c_ = juce::Colours::white;
		this->drawBackground(g);
		g.setColour(juce::Colours::black);
		g.setFont(stoej::get_font_archivo_narrow());
		g.setFont(13.0f * dp_ * stoej::PT_2_PX);
		g.drawText(this->label_off_, r, juce::Justification::centred);
	}
	this->drawBorder(g);
}

void stoej::StoejButton::paintIcon(juce::Graphics& g, bool pressed)
{
	auto r = this->getLocalFloatBounds();
	if (pressed) {
		this->background_c_ = juce::Colours::black;
		this->drawBackground(g);
		// TODO: drawables should be stored as paths, instead of this recolouring bullshite
		this->icon_on_->replaceColour(stoej::Colours::meta_unassigned, juce::Colours::white);
		this->icon_on_->drawWithin(g, icon_on_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
		this->icon_on_->replaceColour(juce::Colours::white, stoej::Colours::meta_unassigned);
	}
	else {
		this->background_c_ = juce::Colours::white;
		this->drawBackground(g);
		this->icon_on_->replaceColour(stoej::Colours::meta_unassigned, juce::Colours::black);
		this->icon_on_->drawWithin(g, icon_on_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
		this->icon_on_->replaceColour(juce::Colours::black, stoej::Colours::meta_unassigned);
	}
	this->drawBorder(g);
}











