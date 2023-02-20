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

    class ThemeManager : public juce::Button::Listener {
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
            {scope_background,juce::Colour(0xff101010)},
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

        // return a copy of the current active theme
        ThemeColors getActiveTheme(bool use_dark_theme) {
            std::scoped_lock l { this->mutex_dark_theme_, this->mutex_light_theme_ };
            if (use_dark_theme) return dark_theme_;
            else return light_theme_;
        }

        // return a copy of the current active theme
        ThemeColors getActiveTheme() {
            std::scoped_lock l{ this->mutex_dark_theme_, this->mutex_light_theme_ };
            if (this->use_dark_theme_.load()) return dark_theme_;
            else return light_theme_;
        }

        // sets the current active theme
        void setActiveTheme(ThemeColors new_theme, bool use_dark_theme) {
            std::scoped_lock l{ this->mutex_dark_theme_, this->mutex_light_theme_ };
            if (use_dark_theme) dark_theme_ = new_theme;
            else light_theme_ = new_theme;
        }

        juce::Colour getDarkThemeColor(ThemeColorNames name) {
            std::scoped_lock l{ this->mutex_dark_theme_ };
            return dark_theme_[name];
        }

        juce::Colour getLightThemeColor(ThemeColorNames name) {
            std::scoped_lock l{ this->mutex_light_theme_ };
            return light_theme_[name];
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
            std::scoped_lock l{ this->mutex_dark_theme_ };
            this->dark_theme_[name] = color;
        }

        void setLightThemeColor(ThemeColorNames name, juce::Colour color) {
            std::scoped_lock l{ this->mutex_light_theme_ };
            this->light_theme_[name] = color;
        }

        void setThemeColor(ThemeColorNames name, bool use_dark_theme, juce::Colour color) {
            if (use_dark_theme) this->setDarkThemeColor(name, color);
            else this->setLightThemeColor(name, color);
        }

        void buttonClicked(juce::Button* b) override {
            this->setUseDarkMode(b->getToggleState());
            if (this->editor_) this->editor_->repaint();
        }

        void setEditor(juce::AudioProcessorEditor* editor) {
            this->editor_ = editor;
        }

        ThemeManager() : dark_theme_(default_dark_theme), light_theme_(default_light_theme) {}
        ThemeManager(ThemeColors dark_theme, ThemeColors light_theme) : dark_theme_(dark_theme), light_theme_(light_theme) {}
        ~ThemeManager() = default;

    protected:
        std::atomic_bool use_dark_theme_ = false;
        ThemeColors dark_theme_;
        std::mutex mutex_dark_theme_;
        ThemeColors light_theme_;
        std::mutex mutex_light_theme_;
        juce::AudioProcessorEditor* editor_ = nullptr;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ThemeManager)
    }; 
}