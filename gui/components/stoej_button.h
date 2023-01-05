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
        StoejButton(const juce::String& name, ButtonSize, const juce::String& label, bool toggleable = false);

        // toggleable button with separate on and off labels
        StoejButton(const juce::String& name, ButtonSize, const juce::String& label_on, juce::String& label_off);

        // simple button with icon, optionally toggleable
        StoejButton(const juce::String& name, ButtonSize, std::unique_ptr<juce::Drawable> icon, bool toggleable = false);

        // toggleable button with separate on and off icons
        StoejButton(const juce::String& name, ButtonSize, std::unique_ptr<juce::Drawable> icon_on, std::unique_ptr<juce::Drawable> icon_off);
        
        std::variant<float, DynamicSize2> getPreferredHeight() override;
        std::variant<float, DynamicSize2> getPreferredWidth() override;
        //void resized() override;
        //void paint(juce::Graphics&) override {}
        
        //void setLabel(juce::String label);
        //void setSeparateOnOffLabels(juce::String label_on, juce::String label_off);
        //void setIcon(std::unique_ptr<juce::Drawable> icon);
        //void setSeparateOnOffLabels(std::unique_ptr<juce::Drawable> icon_on, std::unique_ptr<juce::Drawable> icon_off);

    private:

        // fat constructor
        StoejButton(
            const juce::String& name,
            ButtonSize size,
            const juce::String& label_on,
            const juce::String& label_off,
            const std::unique_ptr<juce::Drawable> icon_on_,
            const std::unique_ptr<juce::Drawable> icon_off_,
            bool toggleable,
            bool separate_on_off_looks,
            bool use_icon);

        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
        void paintOn();
        void paintOff();

        ButtonSize btn_size_;
        const std::unique_ptr<juce::Drawable> icon_on_;
        const std::unique_ptr<juce::Drawable> icon_off_;
        const juce::String& label_on_;
        const juce::String& label_off_;
        bool separate_on_off_looks_;
        bool use_icon_;
        //Box bounding_box_;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StoejButton)
    };
}