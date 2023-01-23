/*
  ==============================================================================

    stoej_properties.h
    Created: 21 Jan 2023 8:54:23pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

namespace stoej {
    struct PropertyInfo {
        const juce::Identifier id;
        const juce::var init;
    };

    namespace strings {
        namespace apvts_children {
            inline const juce::Identifier internal_properties_state = "bd5BVCqWx1qzHkHbnEGf0";
        }
        namespace internal_properties {
            inline const std::string gui_scale = "internal_properties::gui_scale";
        }
    }

    inline const std::map<std::string, PropertyInfo> properties = {
        { strings::internal_properties::gui_scale, { "Y0mDh-wQe8r6rXT6bA_QD", 2.0f }}
    };
}