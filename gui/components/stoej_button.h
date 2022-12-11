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


//==============================================================================
/*
*/
namespace stoej {
    class StoejButton : public juce::Button, public stoej::IResizableComponent, public stoej::ITileableComponent {
	    
    public:
	    /// @note `e_icon` ignores `ButtonSize`. It is always the same size as `e_tiny`.
	    enum ButtonVariant {e_text, e_icon};
        enum ButtonSize {e_tiny, e_small, e_medium, e_large};

        StoejButton(const juce::String& button_name, ButtonVariant, ButtonSize, bool toggleable);
        std::variant<int, DynamicSize> getHeight() override;
        std::variant<int, DynamicSize> getWidth() override;
        void setDP(double dp) override;
	    void setTilePosition(TilePosition) override;
        void resized() override;
        void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    private:
        double dp_ = 1.0;
        TilePosition tile_position_ = e_all_edges;
        ButtonVariant btn_variant_;
        ButtonSize btn_size_;
        Box bounding_box_;
    };
}