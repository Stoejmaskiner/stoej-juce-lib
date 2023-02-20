/*
  ==============================================================================

    StoejComponent.h
    Created: 1 Sep 2022 12:15:13pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <variant>

namespace stoej {

	// let the parent choose the size dynamically according to one of several
	// strategies.
	// - e_fill_parent: bounds should be set to be as large as the parent component
	// has room for
	// - e_parent_decides: the parent can choose the size of the component freely,
	//   for example when building a composite component out of simple primitives
	//
	// Note that this is just a suggestion to the parent, not a hard requirement
	enum [[deprecated]] DynamicSize { e_fill_parent, e_parent_decides };

	class [[deprecated]] IResizableComponent {
	public:
		// used to signal to parent how to decide size for this component
		// in .setBounds(). Exact value represents unscaled size. The size
		// of the component with an exact size preference will still be
		// subject to scaling, but only proportionally to scaling factor
		//
		// the implementation should contain all logic necessary to determine
		// the preferred size, this might not be trivial for composite components
		// with dynamic children.
		//
		// note that in most cases the type of the return variant is obvious
		// and can safely be unpacked without matching all cases
		virtual std::variant<int, DynamicSize> getHeight() = 0;

		// used to signal to parent how to decide size for this component
		// in .setBounds(). Exact value represents unscaled size. The size
		// of the component with an exact size preference will still be
		// subject to scaling, but only proportionally to scaling factor
		//
		// the implementation should contain all logic necessary to determine
		// the preferred size, this might not be trivial for composite components
		// with dynamic children.
		//
		// note that in most cases the type of the return variant is obvious
		// and can safely be unpacked without matching all cases
		virtual std::variant<int, DynamicSize> getWidth()  = 0;

		// parent will call this before setting bounds, this is the scaling
		// factors to be passed to all children. The dynamic size of children
		// is equal to their preferred size in pixels times the scaling factor
		//
		// in the implementation, this should call setDP on all child components
		virtual void setDP(double dp) = 0;

	};
}
