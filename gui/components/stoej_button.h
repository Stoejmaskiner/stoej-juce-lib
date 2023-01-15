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
#include "binary_data/stoej_Icon.h"
#include "binary_data/stoej_Svgs.h"


//==============================================================================
/*
*/
namespace stoej {
    class StoejButton : public stoej::FloatComponent<juce::Button> {
	    
    public:
	    
        enum ButtonSize {tiny, small, medium, large};

        // simple button with text label, optionally toggleable
        StoejButton(const juce::String name, ButtonSize size, const juce::String label, bool toggleable = false)
            : StoejButton(name, size, label, label, nullptr, nullptr, toggleable, false) {}

        // toggleable button with separate on and off labels
        StoejButton(const juce::String name, ButtonSize size, const juce::String label_on, juce::String& label_off)
            : StoejButton(name, size, label_on, label_off, nullptr, nullptr, true, false) {}

        // simple button with icon, optionally toggleable
        StoejButton(const juce::String name, ButtonSize size, stoej::Icon* const icon, bool toggleable = false)
            : StoejButton(name, size, "", "", icon, icon, toggleable, true) {}

        // toggleable button with separate on and off icons
        StoejButton(const juce::String name, ButtonSize size, stoej::Icon* const icon_on, stoej::Icon* const icon_off)
            : StoejButton(name, size, "", "", icon_on, icon_off, true, true) {}
        
        std::variant<float, DynamicSize2> getPreferredHeight() override;
        std::variant<float, DynamicSize2> getPreferredWidth() override;
        void resized() override;
        //void resized() override;
        //void paint(juce::Graphics&) override {}
        
        //void setLabel(juce::String label);
        //void setSeparateOnOffLabels(juce::String label_on, juce::String label_off);
        //void setIcon(std::unique_ptr<juce::Drawable> icon);
        //void setSeparateOnOffLabels(std::unique_ptr<juce::Drawable> icon_on, std::unique_ptr<juce::Drawable> icon_off);

    private:

        // fat constructor
        StoejButton(
            const juce::String name,
            ButtonSize size,
            const juce::String label_on,
            const juce::String label_off,
            stoej::Icon* const icon_on_,
            stoej::Icon* const icon_off_,
            bool toggleable,
            bool use_icon);

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

        // TODO: consider inlining these?
        //void paintOneIcon(juce::Graphics& g, bool pressed);
        //void paintTwoIcons(juce::Graphics& g, bool pressed);
        //void paintOneLabel(juce::Graphics& g, bool pressed);
        //void paintTwoLabels(juce::Graphics& g, bool pressed);
        void paintLabel(juce::Graphics& g, bool pressed);
        void paintIcon(juce::Graphics& g, bool pressed);

        ButtonSize btn_size_;
        //const std::unique_ptr<juce::Drawable>& icon_on_;
        //const std::unique_ptr<juce::Drawable>& icon_off_;
        std::optional<stoej::Icon> icon_on_;
        std::optional<stoej::Icon> icon_off_;
        const juce::String label_on_;
        const juce::String label_off_;
        bool use_icon_;
        //Box bounding_box_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoejButton)
    };
}