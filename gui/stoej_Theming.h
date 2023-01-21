/*
  ==============================================================================

    stoej_Theming.h
    Created: 19 Jan 2023 12:09:03am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

#define STOEJ_DEF_THEME_COLOR_(subtheme, name, col) \
namespace subtheme { \
    inline const stoej::ThemeColorInfo name = { \
        "stoej_" #subtheme "_" #name, \
        col \
    }; \
}

#define STOEJ_SET_THEME_COLOR_(vt, name) \
vt.setProperty(name.id, name.default_value, nullptr);


namespace stoej {
    struct ThemeColorInfo {
        juce::Identifier id;
        juce::int64 default_value;
    };

    namespace theme_colours {
        STOEJ_DEF_THEME_COLOR_(light_theme, text_primary, 0xff000000);
        STOEJ_DEF_THEME_COLOR_(light_theme, text_inverted, 0xfffefefe);
        STOEJ_DEF_THEME_COLOR_(light_theme, text_secondary, 0xff7f7f7f);
        STOEJ_DEF_THEME_COLOR_(light_theme, foreground_primary, 0xff000000);
        STOEJ_DEF_THEME_COLOR_(light_theme, background_primary, 0xfffefefe);
        STOEJ_DEF_THEME_COLOR_(light_theme, background_secondary, 0xffeeeeee);
        STOEJ_DEF_THEME_COLOR_(light_theme, fill_primary, 0xffff20a0);
        STOEJ_DEF_THEME_COLOR_(light_theme, fill_secondary, 0xffaaaaaa);
        STOEJ_DEF_THEME_COLOR_(light_theme, scope_background, 0xff202020);

        STOEJ_DEF_THEME_COLOR_(dark_theme, text_primary, 0xffffffff);
        STOEJ_DEF_THEME_COLOR_(dark_theme, text_inverted, 0xff303030);
        STOEJ_DEF_THEME_COLOR_(dark_theme, text_secondary, 0xff7f7f7f);
        STOEJ_DEF_THEME_COLOR_(dark_theme, foreground_primary, 0xffffffff);
        STOEJ_DEF_THEME_COLOR_(dark_theme, background_primary, 0xff303030);
        STOEJ_DEF_THEME_COLOR_(dark_theme, background_secondary, 0xff101010);
        STOEJ_DEF_THEME_COLOR_(dark_theme, fill_primary, 0xffff20a0);
        STOEJ_DEF_THEME_COLOR_(dark_theme, fill_secondary, 0xffffffff);
        STOEJ_DEF_THEME_COLOR_(dark_theme, scope_background, 0xff101010);
    }

    // return default theme. Note that you will likely want to 
    // override some of the colors for each plugin you make
    // note that components assume the name of the theme property
    // to be `stoej_theme`
    [[deprecated("use stoej::APVTS instead")]]
    inline void load_default_theme(juce::ValueTree& theme) {
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::text_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::text_inverted);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::text_secondary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::foreground_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::background_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::background_secondary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::fill_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::fill_secondary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::light_theme::scope_background);

        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::text_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::text_inverted);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::text_secondary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::foreground_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::background_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::background_secondary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::fill_primary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::fill_secondary);
        STOEJ_SET_THEME_COLOR_(theme, theme_colours::dark_theme::scope_background);
    }

    [[deprecated("use stoej::APVTS instead")]]
    inline juce::Colour fetch_theme_colour(juce::AudioProcessorValueTreeState& apvts, const juce::Identifier id) {
        // TODO: sanity checks?
        return juce::Colour(juce::int32(apvts.state.getProperty(id)));
    }
}

#undef STOEJ_DEF_THEME_COLOR_
#undef STOEJ_SET_THEME_COLOR_