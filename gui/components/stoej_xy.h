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
    class XY : public stoej::FloatComponent<juce::Component>, juce::Value::Listener {
    public:
        XY();
        void paint(juce::Graphics& g) override;
        void mouseDown(const juce::MouseEvent& e) override;
        void mouseDrag(const juce::MouseEvent& e) override;
        void valueChanged(juce::Value& _) override { this->repaint(); }
        //void valueChanged(juce::Value& value) { this->repaint(); }

        // TODO: interface with APVTS directly to avoid dependence on sliders

        juce::Value& getXValueObject();
        juce::Value& getYValueObject();

    private:
        juce::Value x_;
        juce::Value y_;
    };
}