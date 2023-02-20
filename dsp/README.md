# DSP Submodule

[TOC]

## Structure

- `/dsp/generators/` contains special juce::dsp processors that act as *generators*, i.e. they ignore the input buffer, but rather fill the output buffer with new data. These are typically oscillators, noise generators, samplers, ...
- `/dsp/processors/` contains juce::dsp processors. These are building blocks for constructing effects.
  - `/dsp/processors/mfx` contains minimalistic pre-made effects (or *micro effects (MFX)*. These are essentially small plugins that can be embedded into larger plugins.

## Generators Documentation

## Processors Documentation

### MFX Documentation

## Dev Guidelines

TODO

## References

TODO