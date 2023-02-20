# Støjmaskiner // Shared Code

[TOC]

```
stoej-juce-lib/
  include/
    StoejHeader.h
  src/
    dsp/
      generators/
        ...
      processors/
        ...
      stoej_Generator.h
      stoej_Processor.h
    gui/
      components/
        ...
      stoej_Component.h
    stoej_core.h
    stoej_APVTS.h
    stoej_parameters.h
```







This is code used in all Støjmaskiner plugins, free or not, open source or not. This code remains free and open source and is a peer into how some of our plugins work.
Please note that this code is intended for use inside of a JUCE project and depends on the JUCE headers being defined. No makefiles or other configuration files are provided
as you are expected to add this library to an existing project as a simple static dependency.

## Submodules Overview

### [Core](core-doc.md)

Basic definitions used across the entire library.

Defined in `stoej_core.h`

### [DSP](dsp/README.md)

Processors and generators are defined here. They all depend on the JUCE dsp namespace.

### [GUI](gui/README.md)

JUCE GUI components are here. These follow a specific API that extends and restricts the standard JUCE GUI API. The API is defined with several interface classes which the components derive from.

### [Utils](utils/README.md)

Various utility functions. Generally small self-contained functions.

### [Templates](templates/README.md)

These are not strictly part of the library, as in they shouldn't be imported. These are just examples that can be copy-pasted to save time.

## Contributing

TODO

## References

TODO





==vvv THIS IS ALL DEPRECATED vvv==

## Submodule: `distortion.hpp`

Simple non-linear functions and more complex distortion constructs. Fast variants are available as well for computation on embedded devices.

### Distortion primitives
These are the bare-bones functions used in the distortion effects, they are not parametrized (i.e. it's just a simple mapping from the input signal to the output signal, with no scaling or biasing). Usually you'd want to use other effects unless you need to implement custom scaling or biasing.
- `soft_sigmoid`: a wrapper around `tanh`, for API consistency
- `medium_sigmoid`: used in `medium_clip`
- `firm_sigmoid`: used in `firm_clip`
- `unity_clamp`: used in `hard_clip` and `safe_clip`
- `signed_ln`: used in `unbounded_dist`
- `fast_soft_sigmoid`, `fast_medium_sigmoid`, `fast_firm_sigmoid`

### `unbounded_dist` and `fast_unbounded_dist`
Soft distortion with no maximal saturation threshold. It is based on the natural log.

### Clippers
All clippers have the same API:

Precise:
```
xxx_clip(input, threshold) -> output
```

Fast:
```
fast_xxx_clip(input, threshold) -> output
```

Full list:
- `soft_clip`: based on `tanh`, reminiscent of FET, tube or tape clipping
- `medium_clip`: slightly harder than `tanh`, reminiscent of germanium diode clipping
- `firm_clip`: analog-style hard clipping, reminiscent of silicon diode clipping
- `hard_clip`: digital hard clipping
- `safe_clip`: digital hard clipping with inter-sample peak clipping
- `sin_clip`: soft clipping based on `sin`, has the property of reaching maximal saturation with finite gain
- `fast_soft_clip`: algebraic soft clipper
- `fast_medium_clip`: algebraic medium clipper
- `fast_firm_clip`: algebraic firm clipper


## Submodule: `math_extensions.hpp`
Extensions to the (lacking) `cmath` standard library

### More trig and hyperbolic functions

### `signum`
Signum returns 1 if the sign of the input is positive, -1 if it is negative and 0 if it is 0. It is faster than any alternative from the standard library.





## Submodule: dsp/transform

Defines matched encoders and decoders to interface from the discrete time linear PCM domain to other domains, such as discrete Fourier domain, u-law PCM, ... Some transformations are fully reversible, some lose information (they are lossy). Some have the deliberate purpose of reducing the size of the signal (compression). Multiple sub-submodules further categorize these.

- Root: misc time-domain lossless transforms
- /compression: lossless and lossy compression
- /spectral: spectral transformations (FFT, DWT, EMD)

### Wave cycle decomposer / composer

Extract single wave cycles from a signal, in order to transform them and then assemble them again. Such a technique can be used for quadrant shaping, pitch detection, click-free audio slicing.

@TODO(Lorenzo): use in shitpressor and saturation for dynamic saturation

### Overlap-add decomposer / composer

Overlap-add is a technique used in STFT (short-term Fourier transform) as well as many other spectral and sometimes non-spectral methods, usually it is used in conjunction with another transform (it wraps around it).

### PWM encoder / decoder

Convert a PCM sample to a PWM pulse train with minimal loss of information and then back again

### PDM encoder / decoder



### Submodule: dsp/transform/spectral

TODO



