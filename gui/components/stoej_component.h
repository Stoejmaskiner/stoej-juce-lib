/*
  ==============================================================================

	StoejComponent.h
	Created: 1 Sep 2022 12:15:13pm
	Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <variant>
#include <JuceHeader.h>
#include <stoej_core.h>
#include "stoej_APVTS.h"
#include "stoej_params.h"
#include "gui/stoej_Theming.h"

constexpr float X_NUDGE = 0.5f;
constexpr float Y_NUDGE = 0.5f;
constexpr bool DEBUG_ENABLE = true;

namespace stoej {

// let the parent choose the size dynamically according to one of several
// strategies.
// - e_fill_parent: bounds should be set to be as large as the parent component
// has room for
// - e_parent_decides: the parent can choose the size of the component freely,
//   for example when building a composite component out of simple primitives
//
// Note that this is just a suggestion to the parent, not a hard requirement
enum DynamicSize2 { fill_parent, parent_decides };

// 4 bit flags to set all borders. You can perform bitwise operations on them,
// for example XOR to toggle some borders while leaving others unaffected.
enum EnabledBorders { 
	none =   0b0000,
	top =    0b0001, 
	right =  0b0010, 
	bottom = 0b0100, 
	left =   0b1000,
	vertical =     left     | right, 
	horizontal =   top      | bottom,
	top_left =     top      | left,
	top_right =    top      | right,
	bottom_right = bottom   | right,
	bottom_left =  bottom   | left,
	left_end =     left     | horizontal,
	top_end =      top      | vertical,
	right_end =    right    | horizontal,
	bottom_end =   bottom   | vertical,
	all =          vertical | horizontal 
};
DEFINE_ENUM_FLAG_OPERATORS(EnabledBorders);

/// <summary>
/// An extension to the JUCE component class, this adds the following features:
/// - Scalability: provide the pixel size with setDP()
/// - Float bounds: use setFloatBounds() instead of setBounds()
/// - Debugging: set the template attribute DebugEnabled to true to show debugging gizmos
/// </summary>
template<class JuceComponent>
class FloatComponent : public JuceComponent {
protected:
	juce::Rectangle<float> floatBounds_;
	float dp_ = 1.0f;

	[[deprecated("unused")]]
	float border_w_ = 0.0f;

	[[deprecated("unused")]]
	juce::Colour border_c_ = juce::Colours::black;

	[[deprecated("unused")]]
	juce::Colour background_c_ = juce::Colours::white;
	EnabledBorders enabled_borders_ = EnabledBorders::all;
	stoej::APVTS& apvts_;
	stoej::ThemeManager& theme_manager_;

	// draw the integer bounds
	void dbgDrawIntBounds(juce::Graphics &g) {
		if constexpr(DEBUG_ENABLE) {
			auto r = JuceComponent::getLocalBounds();
			g.setColour(juce::Colour(0x80ff0000));
			g.drawRect(r);
		}
	}

	// draw the float bounds
	void dbgDrawFloatBounds(juce::Graphics& g) {
		if constexpr(DEBUG_ENABLE) {
			auto r = this->getLocalFloatBounds();
			g.setColour(juce::Colours::blue);
			g.drawRect(r);
		}
	}

	// draw an outline around the component
	void drawBorder(juce::Graphics& g, float w, juce::Colour c) {
			
		// early return if no borders need to be drawn
		if (this->enabled_borders_ == EnabledBorders::none) return;

		jassert(w >= 0.0f);

		// TODO: tune threshold size to minimum visible on black background
		if (w <= 0.05f) return;

		auto r = this->getLocalFloatBounds();
		auto tl = r.getTopLeft();
		auto br = r.getBottomRight();
		auto tr = r.getTopRight();
		auto bl = r.getBottomLeft();
		g.setColour(c);

		juce::Path p;

		switch (this->enabled_borders_) {
		case all:
			p.addRectangle(r);
			break;
		case top:
			p.startNewSubPath(tl);
			p.lineTo(tr);
			break;
		case right:
			p.startNewSubPath(tr);
			p.lineTo(br);
			break;
		case bottom:
			p.startNewSubPath(br);
			p.lineTo(bl);
			break;
		case left:
			p.startNewSubPath(bl);
			p.lineTo(tl);
			break;

		case vertical:
			p.startNewSubPath(tr);
			p.lineTo(br);
			p.startNewSubPath(bl);
			p.lineTo(tl);
			break;
		case horizontal:
			p.startNewSubPath(tl);
			p.lineTo(tr);
			p.startNewSubPath(br);
			p.lineTo(bl);
			break;

		case top_left:
			p.startNewSubPath(bl);
			p.lineTo(tl);
			p.lineTo(tr);
			break;
		case top_right:
			p.startNewSubPath(tl);
			p.lineTo(tr);
			p.lineTo(br);
			break;
		case bottom_right:
			p.startNewSubPath(tr);
			p.lineTo(br);
			p.lineTo(bl);
			break;
		case bottom_left:
			p.startNewSubPath(br);
			p.lineTo(bl);
			p.lineTo(tl);
			break;


		case top_end:
			p.startNewSubPath(bl);
			p.lineTo(tl);
			p.lineTo(tr);
			p.lineTo(br);
			break;
		case right_end:
			p.startNewSubPath(tl);
			p.lineTo(tr);
			p.lineTo(br);
			p.lineTo(bl);
			break;
		case bottom_end:
			p.startNewSubPath(tr);
			p.lineTo(br);
			p.lineTo(bl);
			p.lineTo(tl);
			break;
		case left_end:
			p.startNewSubPath(br);
			p.lineTo(bl);
			p.lineTo(tl);
			p.lineTo(tr);
			break;

		default:
			// all cases should be taken care of by this point
			jassertfalse;
		}

		g.strokePath(p, juce::PathStrokeType(w * dp_, juce::PathStrokeType::JointStyle::mitered));

		//this->dbgDrawIntBounds(g);
		//this->dbgDrawFloatBounds(g);
	}
	
	void drawBackground(juce::Graphics& g, juce::Colour c) {
		auto r = this->getLocalFloatBounds();
		g.setColour(c);
		g.fillRect(r);
	}

public:
	FloatComponent(stoej::ThemedAPVTS& apvts, const juce::String& component_name) : apvts_(apvts), JuceComponent(component_name) {}
	FloatComponent(stoej::ThemedAPVTS& apvts) : apvts_(apvts), JuceComponent() {}
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
	//virtual std::variant<float, DynamicSize> getPreferredWidth() = 0;
	virtual std::variant<float, DynamicSize2> getPreferredWidth() { return DynamicSize2::parent_decides; }
	virtual std::variant<float, DynamicSize2> getPreferredHeight() { return DynamicSize2::parent_decides; }
	//virtual void paint(juce::Graphics& g) override { this->drawBorder(g); }

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
	//virtual std::variant<float, DynamicSize> getPreferredHeight() = 0;

	// parent will call this before setting bounds, this is the scaling
	// factors to be passed to all children. The dynamic size of children
	// is equal to their preferred size in pixels times the scaling factor
	//
	// in the implementation, this should call setDP on all child components
	virtual void setDP(float dp) { this->dp_ = dp; }

	//TODO: implement rest of the box model?
	[[deprecated("unused")]]
	void setBorderWidth(float w) { this->border_w_ = w; }

	[[deprecated("unused")]]
	void setBorderColor(juce::Colour c) { this->border_c_ = c; }

	void setFloatBounds(juce::Point<float> top_left, juce::Point<float> bottom_right) {
		this->setFloatBounds(juce::Rectangle<float>(top_left, bottom_right));
	}

	void setFloatBounds(float start_x, float start_y, float width, float height) {
		this->setFloatBounds(juce::Rectangle<float>(start_x, start_y, width, height));
	}

	void setFloatBounds(juce::Rectangle<int> r) {
		this->setFloatBounds(juce::Rectangle<float>(r.getTopLeft().getX(), r.getTopLeft().getY(), r.getWidth(), r.getHeight()));
	}

	void setFloatBounds(juce::Rectangle<float> r) {
		this->floatBounds_ = r;
		auto top_left = r.getTopLeft();
		auto bottom_right = r.getBottomRight();
		// FIXME: here the -1, and +1 are superfluous but necessary in some (which?) edge cases. It only happens at init time
		int left = juce::roundToInt(std::floor(top_left.getX() - this->border_w_ * dp_ * 0.5f + X_NUDGE)) - 1;
		int top = juce::roundToInt(std::floor(top_left.getY() - this->border_w_ * dp_ * 0.5f + Y_NUDGE)) - 1;
		int right = juce::roundToInt(std::ceil(bottom_right.getX() + this->border_w_ * dp_ * 0.5f + X_NUDGE)) + 1;
		int bottom = juce::roundToInt(std::ceil(bottom_right.getY() + this->border_w_ * dp_ * 0.5f + Y_NUDGE)) + 1;
		this->setBounds(left, top, right - left, bottom - top);
	}

	juce::Rectangle<float> getFloatBounds() {
		return this->floatBounds_;
	}

	juce::Rectangle<float> getLocalFloatBounds() {
		return this->floatBounds_ + juce::Point<float>(X_NUDGE, Y_NUDGE) - juce::Point<float>(JuceComponent::getX(), JuceComponent::getY());
	}

	// sets all borders
	void setEnabledBorders(EnabledBorders b) {
		this->enabled_borders_ = b;
	}
		
	// enables selected, leaves others unchanged (bitwise OR)
	void enableBorders(EnabledBorders b) {
		this->enabled_borders_ |= b;
	}

	// keeps selected unchanged, disables remaining (bitwise AND)
	void disableBorders(EnabledBorders b) {
		this->enabled_borders_ &= b;
	}

	// flips selected, leaves remaining unchanged (bitwise XOR)
	void toggleBorders(EnabledBorders b) {
		this->enabled_borders_ ^= b;
	}

	EnabledBorders getEnabledBorders() {
		return this->enabled_borders_;
	}

	bool areAllBordersEnabled() {
		return this->enabled_borders_ == EnabledBorders::all;
	}
};
}
