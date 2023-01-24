/*
  ==============================================================================

    stoej_Slider.cpp
    Created: 15 Dec 2022 9:03:00pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_Slider.h"

stoej::StoejSlider::StoejSlider(stoej::ThemedAPVTS& apvts, const juce::String& component_name, const char* label, ValueUnit unit, bool is_inverted) :
    stoej::FloatComponent<juce::Slider>(apvts, component_name), label_(label), is_inverted_(is_inverted), unit_(unit)
{
    this->setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    this->setBorderWidth(1.0f);
    this->setRange(0.0, 1.0);
    this->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    //this->addAndMakeVisible(this->label_box_);
    //this->addAndMakeVisible(this->value_box_);
    // TODO: screenreader support
    // TODO: editable value
    // TODO: custom mouse area to drawn slider only
}

/*
void stoej::StoejSlider::resized()
{
    auto r = this->getLocalBounds();
    this->label_box_.setBounds(r.removeFromTop(18.f * dp_));
    this->value_box_.setBounds(r.removeFromTop(18.f * dp_));
}
*/



void stoej::StoejSlider::paint(juce::Graphics& g)
{
    auto r = this->getLocalFloatBounds();
    auto r1 = r.removeFromTop(18.f * dp_);
    auto r2 = r.removeFromTop(18.f * dp_);
    r.removeFromLeft(12.f * dp_);
    r.removeFromRight(12.f * dp_);
    auto r3 = juce::Rectangle(r);
    //this->drawBackground(g);
    //this->drawBorder(g);
    
    // TODO: macro this, it's reused a lot. Call it something like "STOEJ_GET_THEME_COLOR_WITH_MODE_APPLIED"
    auto bg_c = this->apvts_.getGenericThemeColorWithModeApplied(strings::generic_theme::background_primary);
    this->drawBackground(g, bg_c);
    //g.setColour(bg);
    //g.fillRect(r);

    auto v = this->getValue();
    auto p = this->valueToProportionOfLength(v);
    if(this->is_inverted_) r3.removeFromBottom(r3.getHeight() * p);
    else r3.removeFromTop(r3.getHeight() * (1. - p));
    auto fill_c = this->apvts_.getGenericThemeColorWithModeApplied(strings::generic_theme::fill_secondary);
    g.setColour(fill_c);
    g.fillRect(r3);
    auto border_c = this->apvts_.getGenericThemeColorWithModeApplied(strings::generic_theme::foreground_primary);
    g.setColour(border_c);
    if(this->is_inverted_) g.drawLine(juce::Line(r3.getBottomLeft(), r3.getBottomRight()), 1.0f * dp_);
    else g.drawLine(juce::Line(r3.getTopLeft(), r3.getTopRight()), 1.0f * dp_);
    auto txt_c = this->apvts_.getGenericThemeColorWithModeApplied(strings::generic_theme::text_primary);
    g.setColour(txt_c);
    stoej::draw_rect_f(g, r, 1.0f * dp_);
    g.setFont(get_font_archivo_narrow());
    g.setFont(12.f * dp_ * stoej::PT_2_PX);
    g.drawText(this->label_, r1, juce::Justification::centred);

    switch (this->unit_) {
    case hertz:
        g.drawText(stoej::format_float_hertz(v), r2, juce::Justification::centred);
        break;
    case percent:
        g.drawText(stoej::format_float_percent(v), r2, juce::Justification::centred);
        break;
    case level2db:
        g.drawText(stoej::format_float_level2db(v), r2, juce::Justification::centred);
        break;
    case no_unit:
    default:
        g.drawText(stoej::format_float_no_unit(v), r2, juce::Justification::centred);
    }
    
}
