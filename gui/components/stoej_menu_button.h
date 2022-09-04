/*
  ==============================================================================

    stoej_menu_button.h
    Created: 1 Sep 2022 7:15:49pm
    Author:  Lorenzo

  ==============================================================================
*/

// TODO(Lorenzo, #2) refactor into separate .h and .cpp

#pragma once

#include <JuceHeader.h>

#include "stoej_box.h"
#include "gui/interfaces/stoej_resizeable_component.h"
#include "gui/interfaces/stoej_tileable_component.h"

//==============================================================================
/*
*/
namespace stoej {
	class MenuButton : public juce::Component, public stoej::IResizableComponent, public stoej::ITileableComponent
	{

	public:
		MenuButton(const std::unique_ptr<juce::Drawable>& icon) : icon_(icon)
		{
			this->addAndMakeVisible(this->bounding_box_);
		}
		~MenuButton() override = default;

		void paint(juce::Graphics& g) override
		{
		}

		void paintOverChildren(juce::Graphics& g) override
		{
			//this->icon_->replaceColour(juce::Colours::black, juce::Colours::red);
			this->icon_->drawWithin(g, this->icon_->getBounds().toFloat(), juce::RectanglePlacement(), 1.0);
		}

		void resized() override {

			auto r = this->getLocalBounds();
			this->bounding_box_.setBounds(r);
			r.reduce(3 * dp_, 3 * dp_);
			this->icon_->setBounds(r);
		}

		std::variant<int, stoej::DynamicSize> getHeight() override { return 24; }
		std::variant<int, stoej::DynamicSize> getWidth() override { return 24; }
		void setDP(double dp) override
		{
			this->bounding_box_.setDP(dp);
			this->dp_ = dp;
		}

		void setTilePosition(TilePosition pos) override
		{
			this->bounding_box_.setTilePosition(pos);
		}

	private:
		const std::unique_ptr<juce::Drawable>& icon_;
		stoej::Box bounding_box_;
		double dp_ = 1.0;
		JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuButton)
	};
}