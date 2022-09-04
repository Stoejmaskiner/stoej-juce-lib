/*
  ==============================================================================

    Box.h
    Created: 1 Sep 2022 12:13:15pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "gui/interfaces/stoej_resizeable_component.h"
#include <gui/interfaces/stoej_tileable_component.h>

//==============================================================================
/*
*/

namespace stoej {
	class Box : public juce::Component, public stoej::IResizableComponent, public stoej::ITileableComponent
	{
	public:
		bool draw_bottom = true;
		bool draw_right = true;
		bool draw_left = true;
		bool draw_top = true;
		double stroke_thickness = 1.0;

		// the higher the sooner the thickness is rounded up when scaling up,
		// can be fine-tuned to obtain a specific thickness at a specific scaling
		double stroke_rounding_bias = 0.3;
		juce::Colour stroke_color = juce::Colour(  0,   0,   0);
		juce::Colour fill_color   = juce::Colour(255, 255, 255);

		Box() = default;
		~Box() override = default;

	    void paint (juce::Graphics& g) override {
			// this code is a bit hard to parse so here's a summary:
			//
			// the box is drawn differently depending on whether it is part of an
			// array or grid of adjacent boxes or not, and where in the array or
			// grid it is.
			//
			// a stand-alone box, not in a grid or array, has full thickness edges
			// on all sides. A box that is adjacent to another box shares an edge
			// with the other box, so it only draws half of the thickness of that
			// edge.
			//
			// For edges that have odd number of pixels in width, by convention,
			// the top and left edges round up and the bottom and right edges
			// round down when halving the thickness.

	        auto r = getLocalBounds();
	        g.setColour(this->fill_color);
	        g.fillAll();
	        g.setColour(this->stroke_color);

			// thickness has to be subtracted from right and bottom coordinates so
			// that the thickness is inward and not outward, which would be clipped
			int thick = this->getScaledThickness();
			int tl_x = r.getX();
			int tl_y = r.getY();
			int tr_x = r.getRight() - thick;
			int tr_y = tl_y;
			int bl_x = tl_x;
			int bl_y = r.getBottom() - thick;
			int height = r.getBottom() - tl_y;
			int width = r.getRight() - tl_x;
			// Left and top edges round up, right and bottom edges round down.
			int half_thick_p = thick / 2 + (thick % 2 != 0);
			int half_thick_m = thick / 2;
			int tr_x_half = r.getRight() - half_thick_m;
			int bl_y_half = r.getBottom() - half_thick_m;

			// Draw the full thickness lines if on the edge of the grid
			// Using fillRect instead of drawLine because it is not antialiased
			// and thus looks sharper and is less expensive to draw
			// Draw half-thickness lines if not on the edge of the grid.
			if (this->draw_left) g.fillRect(tl_x, tl_y, thick, height);
			else g.fillRect(tl_x, tl_y, half_thick_p, height);
			if (this->draw_top) g.fillRect(tl_x, tl_y, width, thick);
			else g.fillRect(tl_x, tl_y, width, half_thick_p);
			if (this->draw_bottom) g.fillRect(bl_x, bl_y, width, thick);
			else g.fillRect(bl_x, bl_y_half, width, half_thick_m);
			if (this->draw_right) g.fillRect(tr_x, tr_y, thick, height);
			else g.fillRect(tr_x_half, tr_y, half_thick_m, height);
	    }

	    std::variant<int, stoej::DynamicSize> getHeight() override {
		    return stoej::DynamicSize::e_parent_decides;
	    }

	    std::variant<int, stoej::DynamicSize> getWidth() override {
		    return stoej::DynamicSize::e_parent_decides;
	    }

		//void doDrawBottom(bool val) override { this->draw_bottom = val; }
		//void doDrawRight(bool val) override { this->draw_right = val; }

		void setTilePosition(TilePosition pos) override
	    {
			this->draw_top = pos & TilePosition::e_grid_top_edge;
			this->draw_left = pos & TilePosition::e_grid_left_edge;
			this->draw_bottom = pos & TilePosition::e_grid_bottom_edge;
			this->draw_right = pos & TilePosition::e_grid_right_edge;
	    }

		void setDP(double dp) override { dp_ = dp; }

		int getScaledThickness()
	    {
			return static_cast<int>(std::max(this->stroke_thickness * dp_ + this->stroke_rounding_bias, 1.0));
	    }

	private:
		double dp_ = 1.0;
	    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Box)
	};
}