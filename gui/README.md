# GUI Submodule

[TOC]

## Structure

- `gui/components` contains JUCE GUI components, these match the style of Støjmaskiner products
- `gui/interfaces` defines the API used by all Støjmaskiner GUI components

## Dev Guidelines

All components should follow the same API, which is more strict than the default JUCE approach to GUI implementation, and expands upon it with some interfaces that components can inherit from.

### `IResizeableComponent` API

This API makes it more straight forward to develop GUIs and makes them more maintainable. It is born from the necessity to develop true GUI scaling, which JUCE GUI is really bad at and offers no good solution out of the box. Currently the idea is that the GUI can be designed with a specific static size in mind, and then can be scaled by using virtual pixels as units of size, which may correspond do a variable number of physical pixels.

In JUCE, each component is responsible for resizing its children if its bounding box changes. The top-level window determines the size of all children. This is not ideal, because we want tight control over the size and spacing of components, and we would like the top-level view to wrap around whatever layout is inside, determining the window size dynamically. This cannot be done cleanly, so instead we've reached a compromise.

The compromise consists in performing a handshake between a component and its children to determine their size, while the top-level window has a fixed aspect ratio that has to be manually set by the developer to snugly fit its contents (not very nice).

The handshake functions like this

1. Top level component size changes, with a fixed aspect ratio.
2. Top level calculates the size of a virtual pixel `dp` as the ratio between the actual size of the window and the unscaled size (hard coded, determined by the design specification)
3. Top level calls `setDP` (defined in `IResizeableComponent` interface) on all children to inform them of the new `dp`
   1. All children call `setDP` on their respective children
4. Top level calls `getHeight` and `getWidth` on all children (defined in `IResizeableComponent` interface) to obtain their unscaled size. Then calculates the bounding boxes for all its children knowing their sizes and `dp`. Some components may return `DynamicSize`, in which case, the parent will have more freedom in setting its bounding box, generally filling the remaining space.
5. Top-level sets bounding boxes of all children
   1. Children will do step 4 with their respective children in their `resized` method (defined in `juce::Component` base class)
6. All components now know their scaled size, and can be drawn.

Essentially, the individual components know their own unscaled size, while the parent knows the scaled size of the container the component is in, and they need the handshake to agree on the component's scaled size.

### `ITileableComponent` API

JUCE GUI has a very annoying feature: the `paint()` method of components cannot paint outside of its bounding box. This may seem like a weird complaint, but it is limiting in many cases, specifically, when we want borders around objects to be centered on the edge of the bounding box, rather than extending inwards.

This becomes an issue when tiling components, because the edges extend inwards, adjacent components will have their edges twice as thick. This is annoying. The `ITileableComponent` API allows to dynamically alter how a component is drawn based on whether it is adjacent to other components, and which sides of the component make contact with adjacent components.

To center the bounding line between adjacent components, they have to split the thickness of the line between the two, so they add up to the correct thickness. For odd thicknesses, by convention, the left and upper edges round up and the bottom and right edges round down.

## References

