/*
  ==============================================================================

    stoej_properties.h
    Created: 21 Jan 2023 8:54:23pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

namespace stoej {
    struct BoolPropertyInfo {
        const char* id;
        const bool init;
    };

    struct FloatPropertyInfo {
        const char* id;
        const float init;
    };

    namespace properties {
        inline constexpr FloatPropertyInfo internal_gui_scale{ "KGGH2Gr4vaxucb-TWmNFk", 1.5f };
    }
}