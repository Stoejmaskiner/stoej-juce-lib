/*
  ==============================================================================

    stoej_core.h
    Created: 27 Aug 2022 2:13:49am
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once
#include <concepts>
#include <JuceHeader.h>

// NOTE: for internal use only!
// defines a templated type FT that satisfies the std::floating_point<FT_> concept
#define STOEJ_FT_ template<typename FT_> requires std::floating_point<FT_>

// boilerplate bitwise operator implementations for enums
// (same as in winnt.h)
#define DEFINE_ENUM_FLAG_OPERATORS(ENUMTYPE) \
inline ENUMTYPE operator | (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) | ((int)b)); } \
inline ENUMTYPE &operator |= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) |= ((int)b)); } \
inline ENUMTYPE operator & (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) & ((int)b)); } \
inline ENUMTYPE &operator &= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) &= ((int)b)); } \
inline ENUMTYPE operator ~ (ENUMTYPE a) { return ENUMTYPE(~((int)a)); } \
inline ENUMTYPE operator ^ (ENUMTYPE a, ENUMTYPE b) { return ENUMTYPE(((int)a) ^ ((int)b)); } \
inline ENUMTYPE &operator ^= (ENUMTYPE &a, ENUMTYPE b) { return (ENUMTYPE &)(((int &)a) ^= ((int)b)); }

#define STOEJ_SEMVER_BUILDER(a,b,c,x) "v"##a##"."##b##"."##c##x

#define STOEJ_STRINGIFY_ID_CHECKED(id) (\
id == id,\
JUCE_STRINGIFY(id))

namespace stoej {
    namespace intern {
        inline void dbg_print_helper_(int thislevel, int loglevel, std::string datetime, std::string classname, std::string funcname, std::string msg) {
            
            std::string levelname;
            switch (thislevel) {
            case 0:
                levelname = "DEBUG";
                break;
            case 1:
                levelname = "INFO";
                break;
            case 2:
                levelname = "WARNING";
                break;
            case 3:
                levelname = "ERROR";
                break;
            case 4:
                levelname = "FATAL";
                break;
            default:
                jassertfalse;
            }
            if (thislevel >= loglevel) DBG(datetime + " [" + levelname + "][" + classname + "][" + funcname + "]: " + msg);
        }
    }
}

#define STOEJ_CAT_3_(a,b,c) JUCE_CONCAT(JUCE_CONCAT(a,b),c)
#define STOEJ_CAT_4_(a,b,c,d) JUCE_CONCAT(STOEJ_CAT_3_(a,b,c),d)

#ifdef BUILD_LOG_LEVEL_
// advanced debug printer
#define STOEJ_DBG(level,msg) {\
stoej::intern::dbg_print_helper_(level, BUILD_LOG_LEVEL_, STOEJ_CAT_3_(__DATE__," ",__TIME__) ,typeid(*this).name(),__func__,msg);\
}
#else
// BUILD_LOG_LEVEL_ is undefined!
#define STOEJ_DBG(level,msg)
#endif

enum SemVerCompareResult {
    invalid,
    eq,
    pre_release_lt,
    pre_release_gt,
    patch_lt,
    patch_gt,
    minor_lt,
    minor_gt,
    major_lt,
    major_gt,
    metadata_ne,
    lt,
    gt,
    lt_breaking,
    gt_breaking,
};

namespace stoej {
    inline SemVerCompareResult semVerCompare(juce::String tag1, juce::String tag2, bool precise = false) {
        // TODO: got here
    }
}