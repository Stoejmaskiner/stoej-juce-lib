/*
  ==============================================================================

    stoej_Ticker.cpp
    Created: 3 Jan 2023 7:35:27pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_Ticker.h"

stoej::Ticker::Ticker(const juce::String& component_name) :
    stoej::FloatComponent<juce::Label>(component_name) 
{
    this->setBorderWidth(1.0);
}

void stoej::Ticker::mouseEnter(const juce::MouseEvent& event)
{
    // HACK: evil dynamic cast, will fail mysteriously if event was not caused by a TooltipClient
    auto c = dynamic_cast<juce::TooltipClient*>(event.eventComponent);
    this->active_tooltip_ = c->getTooltip();
    this->repaint();
}

void stoej::Ticker::mouseExit(const juce::MouseEvent& event)
{
}

void stoej::Ticker::paint(juce::Graphics& g)
{
    auto r = this->getLocalFloatBounds();
    g.setFont(get_font_archivo_narrow());   // TODO: atkinson
    g.setFont(12.f * dp_ * stoej::PT_2_PX);
    g.drawText(this->active_tooltip_, r, juce::Justification::centred);
    this->drawBorder(g);
}
