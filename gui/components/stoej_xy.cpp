/*
  ==============================================================================

    stoej_xy.cpp
    Created: 4 Oct 2022 9:05:22pm
    Author:  Lorenzo

  ==============================================================================
*/

#include "stoej_xy.h"

stoej::XY::XY(stoej::APVTS& apvts, stoej::ThemeManager& theme_manager)
    : stoej::FloatComponent<juce::Component>(apvts, theme_manager)
{
    this->x_.addListener(this);
    this->y_.addListener(this);
}

void stoej::XY::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::magenta);
    g.drawVerticalLine((float) this->x_.getValue() * this->getLocalFloatBounds().getWidth(), this->getLocalFloatBounds().getTopLeft().y, this->getLocalFloatBounds().getBottomLeft().y);
    g.drawHorizontalLine((float) this->y_.getValue() * this->getLocalFloatBounds().getHeight(), this->getLocalFloatBounds().getTopLeft().x, this->getLocalFloatBounds().getTopRight().x);
    
    // TODO:
    this->drawBorder(g, 1.f, juce::Colours::black);
    // TODO: this is wrong
}

void stoej::XY::mouseDown(const juce::MouseEvent& e)
{
    float x = e.getMouseDownX() / this->getLocalFloatBounds().getWidth();
    float y = e.getMouseDownY() / this->getLocalFloatBounds().getHeight();
    this->x_ = this->x_range_.convertFrom0to1(stoej::clamp(x, 0.f, 1.f));
    this->y_ = this->y_range_.convertFrom0to1(stoej::clamp(1.f - y, 0.f, 1.f));
    this->repaint();
}

void stoej::XY::mouseDrag(const juce::MouseEvent& e)
{
    float x = e.x / this->getLocalFloatBounds().getWidth();
    float y = e.y / this->getLocalFloatBounds().getHeight();
    this->x_ = this->x_range_.convertFrom0to1(stoej::clamp(x, 0.f, 1.f));
    this->y_ = this->y_range_.convertFrom0to1(stoej::clamp(1.f - y, 0.f, 1.f));
    this->repaint();
}

juce::Value& stoej::XY::getXValueObject()
{
    return this->x_;
}

juce::Value& stoej::XY::getYValueObject()
{
    return this->y_;
}
