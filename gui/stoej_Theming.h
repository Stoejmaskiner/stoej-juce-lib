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

    // a Meyers singleton storing the currently loaded theme
    class ThemeManager {
    public:
        enum ThemeColorNames {
            text_primary,
            text_inverted,
            text_secondary,
            foreground_primary,
            background_primary,
            background_secondary,
            fill_primary,
            fill_secondary,
            scope_background,
        };
        using ThemeColors = std::map<ThemeColorNames, juce::Colour>;

        inline static const ThemeColors default_dark_theme = {
            {text_primary,juce::Colour(0xffffffff)},
            {text_inverted,juce::Colour(0xff303030)},
            {text_secondary,juce::Colour(0xff7f7f7f)},
            {foreground_primary,juce::Colour(0xffffffff)},
            {background_primary,juce::Colour(0xff303030)},
            {background_secondary,juce::Colour(0xff101010)},
            {fill_primary,juce::Colour(0xffff20a0)},
            {fill_secondary,juce::Colour(0xffffffff)},
            {scope_background,juce::Colour(0xfff10101)},
        };
        inline static const ThemeColors default_light_theme = {
            {text_primary,juce::Colour(0xff000000)},
            {text_inverted,juce::Colour(0xfffefefe)},
            {text_secondary,juce::Colour(0xff7f7f7f)},
            {foreground_primary,juce::Colour(0xff000000)},
            {background_primary,juce::Colour(0xfffefefe)},
            {background_secondary,juce::Colour(0xffeeeeee)},
            {fill_primary,juce::Colour(0xffff20a0)},
            {fill_secondary,juce::Colour(0xffaaaaaa)},
            {scope_background,juce::Colour(0xff202020)},
        };

        // return an atomic reference to the theme
        std::atomic<ThemeColors>& getActiveTheme(bool use_dark_theme) {
            if (use_dark_theme) return dark_theme;
            else return light_theme;
        }

        // return a copy of the current active theme
        ThemeColors getRawActiveTheme(bool use_dark_theme) {
            if (use_dark_theme) return dark_theme.load();
            else return light_theme.load();
        }

        // sets the current active theme
        void setActiveTheme(ThemeColors new_theme, bool use_dark_theme) {
            if (use_dark_theme) dark_theme.store(new_theme);
            else light_theme.store(new_theme);
        }

        juce::Colour getDarkThemeColor(ThemeColorNames name) {
            return dark_theme.load()[name];
        }

        juce::Colour getLightThemeColor(ThemeColorNames name) {
            return light_theme.load()[name];
        }

        juce::Colour getThemeColor(ThemeColorNames name, bool use_dark_theme) {
            if (use_dark_theme) return this->getDarkThemeColor(name);
            else return this->getLightThemeColor(name);
        }

        void setDarkThemeColor(ThemeColorNames name, juce::Colour color) {
            // this is a bit inefficient, but the alternative is mutexes and those are hard to pass around
            auto cur_theme = dark_theme.load();
            cur_theme[name] = color;
            dark_theme.store(cur_theme);
        }

        void setLightThemeColor(ThemeColorNames name, juce::Colour color) {
            // this is a bit inefficient, but the alternative is mutexes and those are hard to pass around
            auto cur_theme = light_theme.load();
            cur_theme[name] = color;
            light_theme.store(cur_theme);
        }

        void setThemeColor(ThemeColorNames name, bool use_dark_theme, juce::Colour color) {
            if (use_dark_theme) this->setDarkThemeColor(name, color);
            else this->setLightThemeColor(name, color);
        }

        ThemeManager() : dark_theme(default_dark_theme), light_theme(default_light_theme) {}
        ~ThemeManager() = default;

    protected:
        std::atomic<ThemeColors> dark_theme;
        std::atomic<ThemeColors> light_theme;

        JUCE_DECLARE_NON_COPYABLE(ThemeManager)
    }; 
}