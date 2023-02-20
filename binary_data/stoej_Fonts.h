/*
  ==============================================================================

    stoej_Fonts.h
    Created: 15 Dec 2022 7:51:07pm
    Author:  Lorenzo

	Singleton 

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include <binary_data/stoej_BinaryData.h>
#include <stoej_core.h>

#define STOEJ_LOAD_FONT_(name, binary_name) \
static const juce::Font& get_font_##name () { \
	static juce::Font name ( \
		juce::Typeface::createSystemTypefaceFor( \
			stoej_BinaryData::binary_name##_ttf, \
			stoej_BinaryData::binary_name##_ttfSize)); \
	return name; \
}

namespace stoej {
	STOEJ_LOAD_FONT_(archivo_thin, ArchivoThin);
	STOEJ_LOAD_FONT_(archivo_black, ArchivoBlack);
	STOEJ_LOAD_FONT_(archivo_narrow, ArchivoNarrowRegular);
	STOEJ_LOAD_FONT_(atkinson_hyperlegible, AtkinsonHyperlegibleRegular);
	STOEJ_LOAD_FONT_(ibm_plex_mono, IBMPlexMonoRegular);
}


#undef STOEJ_LOAD_FONT_

/*static const juce::Font& get_font_archivo_narrow_light() {
	static juce::Font archivo_narrow_light(
		juce::Typeface::createSystemTypefaceFor(
			stoej_BinaryData::Archivo_NarrowLight_ttf,
			stoej_BinaryData::Archivo_CondensedLight_ttfSize));

	return archivo_narrow_light;
}

static const juce::Font& get_font_archivo_narrow_bold() {
	static juce::Font archivo_narrow_bold(
		juce::Typeface::createSystemTypefaceFor(
			stoej_BinaryData::Archivo_CondensedBold_ttf,
			stoej_BinaryData::Archivo_CondensedBold_ttfSize));

	return archivo_narrow_bold;
}*/