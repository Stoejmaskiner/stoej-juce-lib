/*
  ==============================================================================

    stoej_Theming.h
    Created: 19 Jan 2023 12:09:03am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

namespace stoej {
    struct ThemeColorInfo {
        juce::Identifier id;
        juce::int64 default_value;
    };

    namespace strings {
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

    inline const std::map<std::string, ThemeColorInfo> theme_colors = {
        { strings::light_theme::text_primary, ThemeColorInfo{ "Y_3ptt8Et7GXmARtiiXB6", 0xff000000 }},
        { strings::light_theme::text_inverted, ThemeColorInfo{ "q_COlB0lzveY-M9S2vcck", 0xfffefefe }},
        { strings::light_theme::text_secondary, ThemeColorInfo{ "TJZVz-GRjVUx8ZWoW36mE", 0xff7f7f7f }},
        { strings::light_theme::foreground_primary, ThemeColorInfo{ "DQkYk6Vuz8EYELi6XIm4b", 0xff000000 }},
        { strings::light_theme::background_primary, ThemeColorInfo{ "9uylYk0uT8qKVsWEy9nkl", 0xfffefefe }},
        { strings::light_theme::background_secondary, ThemeColorInfo{ "rO8XcbAgrCHl7baYCvdmu", 0xffeeeeee }},
        { strings::light_theme::fill_primary, ThemeColorInfo{ "X2_F8AVNRzO2721rV44fb", 0xffff20a0 }},
        { strings::light_theme::fill_secondary, ThemeColorInfo{ "4gDxKasxOs4oqqQ1lqftC", 0xffaaaaaa }},
        { strings::light_theme::scope_background, ThemeColorInfo{ "w_WKjo46xZvA-mPcPm90Z", 0xff202020 }},
        { strings::dark_theme::text_primary, ThemeColorInfo{ "AZjsucEdNeEw9neWv1t2c", 0xffffffff }},
        { strings::dark_theme::text_inverted, ThemeColorInfo{ "SlmHE5LSepv0h-HhzKuft", 0xff303030 }},
        { strings::dark_theme::text_secondary, ThemeColorInfo{ "7d5Y1o64Dp6mJU8MxfYXR", 0xff7f7f7f }},
        { strings::dark_theme::foreground_primary, ThemeColorInfo{ "-TQcYjuQ0uNyA5GSJNnOD", 0xffffffff }},
        { strings::dark_theme::background_primary, ThemeColorInfo{ "OdgJeF_uB2zHPlqdrkgfl", 0xff303030 }},
        { strings::dark_theme::background_secondary, ThemeColorInfo{ "2E8Tn-SqI671_fpzjgLJZ", 0xff101010 }},
        { strings::dark_theme::fill_primary, ThemeColorInfo{ "cbYGd90mz7VDPDFrvrhNO", 0xffff20a0 }},
        { strings::dark_theme::fill_secondary, ThemeColorInfo{ "z8pGjSib18wnnFB3StNUY", 0xffffffff }},
        { strings::dark_theme::scope_background, ThemeColorInfo{ "Rdr_s0jc3OEgDSxpS8eLM", 0xff101010 }}
    };
}

#undef STOEJ_DEF_THEME_COLOR_
#undef STOEJ_SET_THEME_COLOR_