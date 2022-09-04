/*
  ==============================================================================

    stoej_tileable_component.h
    Created: 4 Sep 2022 3:01:56pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

namespace stoej
{
	enum TilePosition
	{
		e_grid_no_edge      = 0b0000,
		e_grid_top_edge     = 0b0001,
		e_grid_left_edge    = 0b0010,
		e_grid_bottom_edge  = 0b0100,
		e_grid_right_edge   = 0b1000,
		e_grid_top_left     = e_grid_top_edge | e_grid_left_edge,
		e_grid_top_right    = e_grid_top_edge | e_grid_right_edge,
		e_grid_bottom_left  = e_grid_bottom_edge | e_grid_left_edge,
		e_grid_bottom_right = e_grid_bottom_edge | e_grid_right_edge,
		e_array_horizontal  = e_grid_top_edge | e_grid_bottom_edge,
		e_array_left        = e_array_horizontal | e_grid_left_edge,
		e_array_right       = e_array_horizontal | e_grid_right_edge,
		e_array_vertical    = e_grid_left_edge | e_grid_right_edge,
		e_array_top         = e_array_vertical | e_grid_top_edge,
		e_array_bottom      = e_array_vertical | e_grid_bottom_edge,
		e_all_edges         = e_array_horizontal | e_array_vertical
	};

	class ITileableComponent
	{
	public:

		/*
		// enable or disable the bottom edge of a bounding box, if this is not
		// applicable just leave the implementation empty
		virtual void doDrawBottom(bool) = 0;

		// enable or disable the right edge of a bounding box, if this is not
		// applicable just leave the implementation empty
		virtual void doDrawRight(bool) = 0;
		*/

		virtual void setTilePosition(TilePosition) = 0;
	};
};