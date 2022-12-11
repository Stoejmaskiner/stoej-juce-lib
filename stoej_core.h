/*
  ==============================================================================

    stoej_core.h
    Created: 27 Aug 2022 2:13:49am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <concepts>

// defines a templated type FT that satisfies the std::floating_point<FT_> concept
#define STOEJ_FT_ template<typename FT_> requires std::floating_point<FT_>

// create a juce::Drawable from binary image data (SVG, etc...)
#define STOEJ_DRAWABLE_IMG(s) (juce::Drawable::createFromImageData(s,s##Size))