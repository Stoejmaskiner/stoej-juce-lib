/*
  ==============================================================================

    stoej_Theming.h
    Created: 19 Jan 2023 12:09:03am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "stoej_properties.h"

namespace stoej {

    namespace strings {
        namespace apvts_children {
            inline const juce::Identifier theme_state = "RzDsV3vGl740yjedVHVbL";
        }
        namespace generic_theme {
            inline const std::string text_primary = "text_primary";
            inline const std::string text_inverted = "text_inverted";
            inline const std::string text_secondary = "text_secondary";
            inline const std::string foreground_primary = "foreground_primary";
            inline const std::string background_primary = "background_primary";
            inline const std::string background_secondary = "background_secondary";
            inline const std::string fill_primary = "fill_primary";
            inline const std::string fill_secondary = "fill_secondary";
            inline const std::string scope_background = "scope_background";
        }
        namespace light_theme {
            inline const std::string text_primary = "light_theme::text_primary";
            inline const std::string text_inverted = "light_theme::text_inverted";
            inline const std::string text_secondary = "light_theme::text_secondary";
            inline const std::string foreground_primary = "light_theme::foreground_primary";
            inline const std::string background_primary = "light_theme::background_primary";
            inline const std::string background_secondary = "light_theme::background_secondary";
            inline const std::string fill_primary = "light_theme::fill_primary";
            inline const std::string fill_secondary = "light_theme::fill_secondary";
            inline const std::string scope_background = "light_theme::scope_background";
        }
        namespace dark_theme {
            inline const std::string text_primary = "dark_theme::text_primary";
            inline const std::string text_inverted = "dark_theme::text_inverted";
            inline const std::string text_secondary = "dark_theme::text_secondary";
            inline const std::string foreground_primary = "dark_theme::foreground_primary";
            inline const std::string background_primary = "dark_theme::background_primary";
            inline const std::string background_secondary = "dark_theme::background_secondary";
            inline const std::string fill_primary = "dark_theme::fill_primary";
            inline const std::string fill_secondary = "dark_theme::fill_secondary";
            inline const std::string scope_background = "dark_theme::scope_background";
        }
    }

    inline const std::map<std::string, PropertyInfo> theme_colors = {
        { strings::light_theme::text_primary, PropertyInfo{ "Y_3ptt8Et7GXmARtiiXB6", juce::int64(0xff000000) }},
        { strings::light_theme::text_inverted, PropertyInfo{ "q_COlB0lzveY-M9S2vcck", juce::int64(0xfffefefe) }},
        { strings::light_theme::text_secondary, PropertyInfo{ "TJZVz-GRjVUx8ZWoW36mE", juce::int64(0xff7f7f7f) }},
        { strings::light_theme::foreground_primary, PropertyInfo{ "DQkYk6Vuz8EYELi6XIm4b", juce::int64(0xff000000) }},
        { strings::light_theme::background_primary, PropertyInfo{ "9uylYk0uT8qKVsWEy9nkl", juce::int64(0xfffefefe) }},
        { strings::light_theme::background_secondary, PropertyInfo{ "rO8XcbAgrCHl7baYCvdmu", juce::int64(0xffeeeeee) }},
        { strings::light_theme::fill_primary, PropertyInfo{ "X2_F8AVNRzO2721rV44fb", juce::int64(0xffff20a0) }},
        { strings::light_theme::fill_secondary, PropertyInfo{ "4gDxKasxOs4oqqQ1lqftC", juce::int64(0xffaaaaaa) }},
        { strings::light_theme::scope_background, PropertyInfo{ "w_WKjo46xZvA-mPcPm90Z", juce::int64(0xff202020) }},
        { strings::dark_theme::text_primary, PropertyInfo{ "AZjsucEdNeEw9neWv1t2c", juce::int64(0xffffffff) }},
        { strings::dark_theme::text_inverted, PropertyInfo{ "SlmHE5LSepv0h-HhzKuft", juce::int64(0xff303030) }},
        { strings::dark_theme::text_secondary, PropertyInfo{ "7d5Y1o64Dp6mJU8MxfYXR", juce::int64(0xff7f7f7f) }},
        { strings::dark_theme::foreground_primary, PropertyInfo{ "-TQcYjuQ0uNyA5GSJNnOD", juce::int64(0xffffffff) }},
        { strings::dark_theme::background_primary, PropertyInfo{ "OdgJeF_uB2zHPlqdrkgfl", juce::int64(0xff303030) }},
        { strings::dark_theme::background_secondary, PropertyInfo{ "2E8Tn-SqI671_fpzjgLJZ", juce::int64(0xff101010) }},
        { strings::dark_theme::fill_primary, PropertyInfo{ "cbYGd90mz7VDPDFrvrhNO", juce::int64(0xffff20a0) }},
        { strings::dark_theme::fill_secondary, PropertyInfo{ "z8pGjSib18wnnFB3StNUY", juce::int64(0xffffffff) }},
        { strings::dark_theme::scope_background, PropertyInfo{ "Rdr_s0jc3OEgDSxpS8eLM",juce::int64( 0xff101010) }}
    };
}

#undef STOEJ_DEF_THEME_COLOR_
#undef STOEJ_SET_THEME_COLOR_