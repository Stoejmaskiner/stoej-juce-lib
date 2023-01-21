/*
  ==============================================================================

    stoej_button.cpp
    Created: 4 Oct 2022 9:04:08pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_button.h"

#include "binary_data/stoej_Fonts.h"
#include "gui/stoej_Theming.h"


stoej::StoejButton::StoejButton(
	stoej::APVTS& apvts,
	const juce::String name,
	ButtonSize size,
	const juce::String label_on,
	const juce::String label_off,
	std::unique_ptr<juce::Drawable> icon_on,
	std::unique_ptr<juce::Drawable> icon_off,
	bool toggleable,
	bool separate_on_off_looks,
	bool use_icon)
	:
	stoej::FloatComponent<juce::Button>(apvts, name),
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
	//this->border_w_ = 1.0f;
	//this->border_c_ = juce::Colours::black;
}


std::variant<float, stoej::DynamicSize2> stoej::StoejButton::getPreferredHeight()
{
    return { 24.f };
}

std::variant<float, stoej::DynamicSize2> stoej::StoejButton::getPreferredWidth()
{
    // TODO: performance tuning with constexpr if and templates?
	switch (this->btn_size_) {
	case tiny:
		return { 24.f };
	case small:
		return { 36.f };
	case medium:
		return { 48.f };
	case large:
		return { 60.f };
	default:
		jassertfalse;
	}
}

void stoej::StoejButton::resized()
{
	//DBG("Button resized: component_name=<" << this->getName() << ">");
	auto r = this->getLocalFloatBounds();
	r.reduce(3 * dp_, 3 * dp_);
	if (this->icon_off_) {
		auto r2 = r.toNearestInt();
		this->icon_off_->setBounds(r2);
	}
	if (this->icon_on_) {
		auto r1 = r.toNearestInt();
		this->icon_on_->setBounds(juce::Rectangle(r1));
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
}

void stoej::StoejButton::paintOneIcon(juce::Graphics& g, bool pressed)
{
	auto maybe_val = this->apvts_.getRawParameterValue(stoej::parameters::internal_use_dark_theme.id);
	bool use_dark_theme = maybe_val ? (*maybe_val >= 0.5f) : false;
	
	if (pressed) {
		auto background_c_ = use_dark_theme ? this->apvts_.getPropertyColourOr(stoej::theme_colours::dark_theme::foreground_primary) : this->apvts_.getPropertyColourOr(stoej::theme_colours::light_theme::foreground_primary);
		this->drawBackground(g, background_c_);
		this->icon_on_->replaceColour(stoej::Colours::meta_unassigned, juce::Colours::white);
		this->icon_on_->drawWithin(g, this->icon_on_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
		this->icon_on_->replaceColour(juce::Colours::white, stoej::Colours::meta_unassigned);
	}
	else {
		// TODO:
		this->drawBackground(g, juce::Colours::white);
		this->icon_on_->replaceColour(stoej::Colours::meta_unassigned, juce::Colours::black);
		this->icon_on_->drawWithin(g, this->icon_on_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
		this->icon_on_->replaceColour(juce::Colours::black, stoej::Colours::meta_unassigned);
	}
	// TODO:
	this->drawBorder(g, 1.f, juce::Colours::black);
}

void stoej::StoejButton::paintTwoIcons(juce::Graphics& g, bool pressed)
{
	if (pressed) {
		// TODO:
		this->drawBackground(g, juce::Colours::black);
		this->icon_on_->replaceColour(stoej::Colours::meta_unassigned, juce::Colours::white);
		this->icon_on_->drawWithin(g, this->icon_on_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
		this->icon_on_->replaceColour(juce::Colours::white, stoej::Colours::meta_unassigned);
	}
	else {
		// TODO:
		this->drawBackground(g, juce::Colours::white);
		this->icon_off_->replaceColour(stoej::Colours::meta_unassigned, juce::Colours::black);
		this->icon_off_->drawWithin(g, this->icon_off_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
		this->icon_off_->replaceColour(juce::Colours::black, stoej::Colours::meta_unassigned);
	}
	// TODO:
	this->drawBorder(g, 1.f, juce::Colours::black);
}

void stoej::StoejButton::paintOneLabel(juce::Graphics& g, bool pressed)
{
	if (pressed) {
		// TODO:
		this->drawBackground(g, juce::Colours::black);
		this->paintLabel(g, this->label_on_, juce::Colours::white);
	}
	else {
		// TODO:
		this->drawBackground(g, juce::Colours::white);
		this->paintLabel(g, this->label_on_, juce::Colours::black);
	}
	// TODO:
	this->drawBorder(g, 1.f, juce::Colours::black);
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









