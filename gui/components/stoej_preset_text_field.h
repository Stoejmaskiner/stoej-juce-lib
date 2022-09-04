/*
  ==============================================================================

    stoej_preset_text_field.h
    Created: 4 Sep 2022 9:25:28pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "stoej_box.h"
#include "gui/interfaces/stoej_resizeable_component.h"
#include "gui/interfaces/stoej_tileable_component.h"
#include "utils/stoej_graphics_utils.h"

//==============================================================================
/*
*/
namespace stoej {
	class PresetTextField  : public juce::Component, public stoej::IResizableComponent, public stoej::ITileableComponent
	{
	public:
		std::string author_string = "Author Name";
		std::string name_string = "Preset Name";
		juce::Colour author_color = juce::Colour(
			juce::uint8(0),
			juce::uint8(0), 
			juce::uint8(0), 
			juce::uint8(128));
		juce::Colour name_color = juce::Colours::black;

	    PresetTextField(
			const juce::Font& name_font,
			const juce::Font& author_font) :
		name_font_(name_font),
		author_font_(author_font)
	    {
	        this->addAndMakeVisible(this->bounding_box_);
	    }

	    ~PresetTextField() override = default;

	    void paint (juce::Graphics& g) override
	    {
			

			/*
			auto r_ico = r.removeFromRight(std::get<int>(this->getHeight()) * dp_);
			r_ico.reduce(6 * dp_, 6 * dp_);
			this->person_ico_->setBounds(r_ico);
			*/
	    }

		void paintOverChildren(juce::Graphics& g) override {
			auto r = this->getLocalBounds();
			r.removeFromRight(6 * dp_);
			g.setColour(this->author_color);
			g.setFont(this->author_font_);
			g.setFont(15.0 * dp_ * stoej::PT_2_PX);
			g.drawText(this->author_string, r.removeFromRight(r.getWidth() / 3), juce::Justification::right, true);

			r.removeFromLeft(6 * dp_);
			g.setColour(this->name_color);
			g.setFont(this->name_font_);
			g.setFont(15.0 * dp_ * stoej::PT_2_PX);
			g.drawText(this->name_string, r, juce::Justification::left, true);

	    }

	    void resized() override
	    {
	        auto r = this->getLocalBounds();
			this->bounding_box_.setBounds(r);
			
	    }

		std::variant<int, DynamicSize> getHeight() override { return 24; }
		std::variant<int, DynamicSize> getWidth() override { return e_fill_parent; }
		void setDP(double dp) override {
		    this->bounding_box_.setDP(dp);
			this->dp_ = dp;
	    }

		void setTilePosition(TilePosition pos) override {
		    this->bounding_box_.setTilePosition(pos);
	    }

	private:
		const juce::Font& name_font_;
		const juce::Font& author_font_;
		Box bounding_box_;
		double dp_ = 1.0;
	    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PresetTextField)
	};
}