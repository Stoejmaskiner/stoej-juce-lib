/*
  ==============================================================================

    stoej_Slider.cpp
    Created: 15 Dec 2022 9:03:00pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_Slider.h"

stoej::StoejSlider::StoejSlider(const juce::String& component_name, const char* label, juce::Slider::SliderStyle style, ValueUnit unit, bool is_inverted) :
    stoej::FloatComponent<juce::Slider>(component_name), label_(label), is_inverted_(is_inverted), unit_(unit)
{
    this->setSliderStyle(style);
    this->setBorderWidth(1.0f);
}

void stoej::StoejSlider::paint(juce::Graphics& g)
{
    this->drawBackground(g);
    
    this->drawBorder(g);
}
