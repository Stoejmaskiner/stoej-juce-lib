/*
  ==============================================================================

    stoej_Icon.h
    Created: 14 Jan 2023 3:09:05pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


namespace stoej {
    struct Icon {
        juce::Path bounds;
        juce::Path path;

        Icon() = default;

        Icon(juce::Path bounds, juce::Path path) {
            this->bounds = bounds;
            this->path = path;
        }

        Icon(const Icon& icon_to_copy) {
            this->bounds = icon_to_copy.bounds;
            this->path = icon_to_copy.path;
        }

        void fit(juce::Rectangle<float> r) {
            auto tr = bounds.getTransformToScaleToFit(r, true);
            this->bounds.applyTransform(tr);
            this->path.applyTransform(tr);
        }
    };
}