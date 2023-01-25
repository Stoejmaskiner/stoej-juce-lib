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

    class ThemeManager : juce::Button::Listener {
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

        void enableDarkMode() { this->use_dark_theme_.store(true); }
        void disableDarkMode() { this->use_dark_theme_.store(false); }
        void toggleDarkMode() { this->use_dark_theme_.store(!this->use_dark_theme_.load()); }
        void setUseDarkMode(bool u) { this->use_dark_theme_.store(u); }
        bool getUseDarkMode() { return this->use_dark_theme_.load(); }

        // return an atomic reference to the theme
        std::atomic<ThemeColors>& getActiveTheme(bool use_dark_theme) {
            if (use_dark_theme) return dark_theme_;
            else return light_theme_;
        }

        // return a copy of the current active theme
        ThemeColors getRawActiveTheme(bool use_dark_theme) {
            if (use_dark_theme) return dark_theme_.load();
            else return light_theme_.load();
        }

        // return an atomic reference to the theme
        std::atomic<ThemeColors>& getActiveTheme() {
            if (this->use_dark_theme_.load()) return dark_theme_;
            else return light_theme_;
        }

        // return a copy of the current active theme
        ThemeColors getRawActiveTheme() {
            if (this->use_dark_theme_.load()) return dark_theme_.load();
            else return light_theme_.load();
        }

        // sets the current active theme
        void setActiveTheme(ThemeColors new_theme, bool use_dark_theme) {
            if (use_dark_theme) dark_theme_.store(new_theme);
            else light_theme_.store(new_theme);
        }

        juce::Colour getDarkThemeColor(ThemeColorNames name) {
            return dark_theme_.load()[name];
        }

        juce::Colour getLightThemeColor(ThemeColorNames name) {
            return light_theme_.load()[name];
        }

        juce::Colour getThemeColor(ThemeColorNames name, bool use_dark_theme) {
            if (use_dark_theme) return this->getDarkThemeColor(name);
            else return this->getLightThemeColor(name);
        }

        juce::Colour getThemeColor(ThemeColorNames name) {
            if (this->use_dark_theme_.load()) return this->getDarkThemeColor(name);
            else return this->getLightThemeColor(name);
        }

        void setDarkThemeColor(ThemeColorNames name, juce::Colour color) {
            // this is a bit inefficient, but the alternative is mutexes and those are hard to pass around
            auto cur_theme = dark_theme_.load();
            cur_theme[name] = color;
            dark_theme_.store(cur_theme);
        }

        void setLightThemeColor(ThemeColorNames name, juce::Colour color) {
            // this is a bit inefficient, but the alternative is mutexes and those are hard to pass around
            auto cur_theme = light_theme_.load();
            cur_theme[name] = color;
            light_theme_.store(cur_theme);
        }

        void setThemeColor(ThemeColorNames name, bool use_dark_theme, juce::Colour color) {
            if (use_dark_theme) this->setDarkThemeColor(name, color);
            else this->setLightThemeColor(name, color);
        }

        void buttonClicked(juce::Button* b) override {
            this->setUseDarkMode(b->getToggleState());
            if (this->editor_) this->editor_->repaint();
        }

        ThemeManager() : dark_theme_(default_dark_theme), light_theme_(default_light_theme) {}
        ThemeManager(juce::AudioProcessorEditor* editor) : dark_theme_(default_dark_theme), light_theme_(default_light_theme), editor_(editor) {}
        ThemeManager(ThemeColors dark_theme, ThemeColors light_theme) : dark_theme_(dark_theme), light_theme_(light_theme) {}
        ThemeManager(juce::AudioProcessorEditor* editor, ThemeColors dark_theme, ThemeColors light_theme) : dark_theme_(dark_theme), light_theme_(light_theme), editor_(editor) {}
        ~ThemeManager() = default;

    protected:
        std::atomic_bool use_dark_theme_ = false;
        std::atomic<ThemeColors> dark_theme_;
        std::atomic<ThemeColors> light_theme_;
        juce::AudioProcessorEditor* editor_ = nullptr;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThemeManager)
    }; 
}