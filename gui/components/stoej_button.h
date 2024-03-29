/*
  ==============================================================================

    stoej_button.h
    Created: 4 Oct 2022 9:04:08pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "stoej_box.h"
#include "gui/interfaces/stoej_resizeable_component.h"
#include "gui/interfaces/stoej_tileable_component.h"
#include "utils/stoej_graphics_utils.h"
#include "stoej_component.h"


//==============================================================================
/*
*/
namespace stoej {
    class StoejButton : public stoej::FloatComponent<juce::Button> {
	    
    public:
	    
        enum ButtonSize {tiny, small, medium, large};

        // simple button with text label, optionally toggleable
        StoejButton(stoej::APVTS* apvts, stoej::ThemeManager& theme_manager, const juce::String name, ButtonSize size, const juce::String label, bool toggleable = false)
            : StoejButton(apvts, theme_manager, name, size, label, "", nullptr, nullptr, toggleable, false, false) {}

        // toggleable button with separate on and off labels
        StoejButton(stoej::APVTS* apvts, stoej::ThemeManager& theme_manager, juce::String name, ButtonSize size, const juce::String label_on, const juce::String label_off)
            : StoejButton(apvts, theme_manager, name, size, label_on, label_off, nullptr, nullptr, true, true, false) {}

        // simple button with icon, optionally toggleable
        StoejButton(stoej::APVTS* apvts, stoej::ThemeManager& theme_manager, const juce::String name, ButtonSize size, std::unique_ptr<juce::Drawable> icon, bool toggleable = false)
            : StoejButton(apvts, theme_manager, name, size, "", "", std::move(icon), nullptr, toggleable, false, true) {}

        // toggleable button with separate on and off icons
        StoejButton(stoej::APVTS* apvts, stoej::ThemeManager& theme_manager, juce::String name, ButtonSize size, std::unique_ptr<juce::Drawable> icon_on, std::unique_ptr<juce::Drawable> icon_off)
            : StoejButton(apvts, theme_manager, name, size, "", "", std::move(icon_on), std::move(icon_off), true, true, true) {}
        
        std::variant<float, DynamicSize2> getPreferredHeight() override;
        std::variant<float, DynamicSize2> getPreferredWidth() override;
        void resized() override;
        void clicked() override { DBG("stoej::StoejButton: clicked: component_name=<" << this->getName() << ">"); }
        void buttonStateChanged() override { 
            juce::String state = this->getToggleState() ? "true" : "false";
            DBG("stoej::StoejButton: state changed: component_name=<" << this->getName() << ">, to_state=<" << state << ">"); 
        }
        //void setSimpleClickAction(std::function<void()> fun) { this->on_click_fun_ = fun; }
        //void paint(juce::Graphics&) override {}
        
        //void setLabel(juce::String label);
        //void setSeparateOnOffLabels(juce::String label_on, juce::String label_off);
        //void setIcon(std::unique_ptr<juce::Drawable> icon);
        //void setSeparateOnOffLabels(std::unique_ptr<juce::Drawable> icon_on, std::unique_ptr<juce::Drawable> icon_off);

    private:

        // fat constructor
        StoejButton(
            stoej::APVTS* apvts,
            stoej::ThemeManager& theme_manager,
            const juce::String name,
            ButtonSize size,
            const juce::String label_on,
            const juce::String label_off,
            std::unique_ptr<juce::Drawable> icon_on_,
            std::unique_ptr<juce::Drawable> icon_off_,
            bool toggleable,
            bool separate_on_off_looks,
            bool use_icon);

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

        // TODO: consider inlining these?
        void paintIcon(juce::Graphics& g, juce::Drawable* icon, juce::Colour color);
        void paintLabel(juce::Graphics& g, juce::StringRef label, juce::Colour c);


        ButtonSize btn_size_;
        std::unique_ptr<juce::Drawable> icon_on_;
        std::unique_ptr<juce::Drawable> icon_off_;
        const juce::String label_on_;
        const juce::String label_off_;
        bool separate_on_off_looks_;
        bool use_icon_;
        std::function<void()> on_click_fun_ = nullptr;
        std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> attachment_;
        //Box bounding_box_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoejButton)
    };
}