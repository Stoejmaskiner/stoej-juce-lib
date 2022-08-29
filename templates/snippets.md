# JUCE Code Snippets

[TOC]

Add these to your snippet expander of choice.

JUCE has *a lot* of boilerplate code, usually it is small things that don't make sense to have as dedicated functions in a library, or it's design patterns that cannot easily be abstracted away into a simple function. Also generally I try to avoid macros, unless I'm doing some high-level DSL programming. So instead I suggest using these snippets instead.

## Defining Parameters APVTS, Super Concise

Add this to public fields of `YourProcessor.h`

**description:** APVTS constructor expects a parameter layout. Unfortunately the parameter layout needs to be constructed in multiple stages (first it is initialized, then the parameters are added) which would require a separate function to do so, which clutters the code base. Instead here I use a closure that is defined and immediately invoked inline.

**suggested binding:** `:juce_def_apvts`

```c++
juce::AudioProcessorValueTreeState apvts{
        *this, nullptr, "Parameters", [](){
            juce::AudioProcessorValueTreeState::ParameterLayout layout;

            layout.add(
                // ... list of parameters here ...
            );
            return layout;
        }()
    };
```

## AudioBuffer to ProcessContextReplacing

**description:** when going from an `AudioProcessor` context to a DSP `Processor` context, you need to convert the `AudioBuffer` to a `ProcessingContext`. This is done every time identically and it is very verbose.

**suggested binding:** `:juce_buff_to_context`

```c++
auto block = juce::dsp::AudioBlock<float>(buffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(block);
```

