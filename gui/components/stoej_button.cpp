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
#include "stoej_APVTS.h"


stoej::StoejButton::StoejButton(
	stoej::APVTS* apvts,
	stoej::ThemeManager& theme_manager,
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
	stoej::FloatComponent<juce::Button>(apvts, theme_manager, name),
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
	if (apvts)
		this->attachment_.reset(
			new juce::AudioProcessorValueTreeState::ButtonAttachment(*apvts, name, *this));
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

	juce::Colour bg_c = pressed ?
		this->theme_manager_.getThemeColor(stoej::ThemeManager::foreground_primary) :
		this->theme_manager_.getThemeColor(stoej::ThemeManager::background_primary);
	juce::Colour txt_c = pressed ?
		this->theme_manager_.getThemeColor(stoej::ThemeManager::text_inverted) :
		this->theme_manager_.getThemeColor(stoej::ThemeManager::text_primary);
	auto border_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::foreground_primary);

	this->drawBackground(g, bg_c);
	if (this->use_icon_)
		if (pressed || !this->separate_on_off_looks_)
			this->paintIcon(g, this->icon_on_.get(), txt_c);
		else this->paintIcon(g, this->icon_off_.get(), txt_c);
	else
		if (pressed || !this->separate_on_off_looks_)
			this->paintLabel(g, this->label_on_, txt_c);
		else this->paintLabel(g, this->label_off_, txt_c);
	this->drawBorder(g, 1.f, border_c);
}



void stoej::StoejButton::paintIcon(juce::Graphics& g, juce::Drawable* icon, juce::Colour color) {
	icon->replaceColour(stoej::Colours::meta_unassigned, color);
	icon->drawWithin(g, icon->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
	icon->replaceColour(color, stoej::Colours::meta_unassigned);
}



void stoej::StoejButton::paintLabel(juce::Graphics& g, juce::StringRef label, juce::Colour c) {
	auto r = this->getLocalFloatBounds();
	g.setColour(c);
	g.setFont(stoej::get_font_archivo_narrow());
	g.setFont(13.0f * dp_ * stoej::PT_2_PX);
	g.drawText(label, r, juce::Justification::centred);
}