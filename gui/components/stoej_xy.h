/*
  ==============================================================================

    stoej_xy.h
    Created: 4 Oct 2022 9:05:22pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "gui/components/stoej_component.h"
#include "utils/stoej_math.h"

namespace stoej {
    class XY : public stoej::FloatComponent<juce::Component>, public juce::Value::Listener {
    public:
        XY();
        void paint(juce::Graphics& g) override;
        void mouseDown(const juce::MouseEvent& e) override;
        void mouseDrag(const juce::MouseEvent& e) override;
        void valueChanged(juce::Value& _) override { this->repaint(); }
        //void valueChanged(juce::Value& value) { this->repaint(); }

        // TODO: interface with APVTS directly with slider attachment or similar

        juce::Value& getXValueObject();
        juce::Value& getYValueObject();
        juce::NormalisableRange<float> getXRange() { return this->x_range_; }
        void setXRange(juce::NormalisableRange<float> r) { this->x_range_ = r; }
        juce::NormalisableRange<float> getYRange() { return this->y_range_; }
        void setYRange(juce::NormalisableRange<float> r) { this->y_range_ = r; }

    protected:
        juce::Value x_;
        juce::Value y_;
        
        juce::NormalisableRange<float> x_range_;
        juce::NormalisableRange<float> y_range_;
    };
}