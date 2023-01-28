/*
  ==============================================================================

    stoej_value.cpp
    Created: 21 Dec 2022 8:33:45pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_value.h"
stoej::Value::Value(stoej::APVTS& apvts, stoej::ThemeManager& theme_manager, const juce::String& component_name, const char* label, ValueUnit unit)
    : stoej::FloatComponent<juce::Slider>(apvts, theme_manager, component_name), label_(label), unit_(unit)
{
    this->setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    this->setBorderWidth(1.0f);
    this->setRange(0.0, 1.0);
    this->setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    //this->addAndMakeVisible(this->label_box_);
    //this->addAndMakeVisible(this->value_box_);
    // TODO: screenreader support
    // TODO: editable value
    // TODO: custom mouse area to drawn slider only
}


void stoej::Value::resized()
{
    this->setMouseDragSensitivity(144 * dp_);
}


void stoej::Value::paint(juce::Graphics& g)
{
    
    auto r = this->getLocalFloatBounds();
    //this->drawBorder(g);
    //this->dbgDrawFloatBounds(g);
    //this->dbgDrawIntBounds(g);
    auto bg_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::background_primary);
    this->drawBackground(g, bg_c);
    auto r1 = r.removeFromTop(18.f * dp_);
    auto r2 = r.removeFromTop(18.f * dp_);
    auto r3 = juce::Rectangle(r);
    //this->drawBackground(g);
    //this->drawBorder(g);

    auto v = this->getValue();
    auto p = this->valueToProportionOfLength(v);
    r3.removeFromRight(r3.getWidth() * (1. - p));

    auto fill_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::fill_secondary);
    g.setColour(fill_c);
    g.fillRect(r3);

    auto border_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::foreground_primary);
    g.setColour(border_c);
    g.drawLine(juce::Line(r3.getTopRight(), r3.getBottomRight()), 1.0f * dp_);
    //g.setColour(this->border_c_);
    stoej::draw_rect_f(g, r, 1.0f * dp_);
    
    auto txt_c = this->theme_manager_.getThemeColor(stoej::ThemeManager::text_primary);
    g.setColour(txt_c);
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

    this->drawBorder(g, 1.f, border_c);

}
