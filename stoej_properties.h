/*
  ==============================================================================

    stoej_properties.h
    Created: 21 Jan 2023 8:54:23pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

// adds a property to the APVTS with the same id as the passed identifier
#define STOEJ_VT_SET_AUTONAMED_PROPERTY(vt,val) {\
vt.setProperty(JUCE_STRINGIFY(val),val,nullptr);\
}

// assert that an autonamed property has the same value as the original symbol
#define STOEJ_VT_ASSERT_AUTONAMED_PROPERTY(vt,val) {\
jassert(vt.getProperty(JUCE_STRINGIFY(val))) == val);\
}

// get a previously autonamed property. If the identifier is undefined, this will fail
#define STOEJ_VT_GET_AUTONAMED_PROPERTY_CHECKED(vt,val) (\
val == val,\
vt.getProperty(JUCE_STRINGIFY(val)))

// compare a previously autonamed property with the original value
#define STOEJ_VT_COMPARE_AUTONAMED_PROPERTY(vt,val) (\
val == vt.getProperty(JUCE_STRINGIFY(val)))

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