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
#include <regex>
#include <string>

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
    invalid = 0,
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


// TODO: try to encapsulate so you don't need namespace intern
namespace stoej {
    namespace intern {
        const std::regex semver_regex_ ("^v?(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})(?:-(\\w+)\\.(\\d{1,2}))?(?:\\+([^ ]+))?$" );
    }
    // compares two SemVer version tags. 
    // With precise = false, it will either return lt, gt, lt_breaking, gt_breaking, invalid or eq
    // With precise = true, it will either return pre_release_lt, pre_release_gt, patch_lt, patch_gt, minor_lt, minor_gt, major_lt, major_gt, metadata_ne
    // 
    // imprecise mode ignores build metadata, and only compares the overall ordering of the two tags. It also marks if the two versions are incompatible
    // Examples:
    // - v2.0.0 <=> v1.99.99 = gt_breaking
    // - v1.1.0 <=> v1.0.0 = gt
    // - v1.1.0+foo <=> v1.1.0+bar = eq
    // 
    // precise mode also takes into account build metadata, and if the two tags are not equal, it also specifies what the highest
    // priority mismatch is.
    // Examples: 
    // - v1.1.0 <=> v2.0.0 = major_lt
    // - v1.1.0 <=> v1.0.0-rc.1 = minor_gt
    // - v1.1.0-rc.1 <=> v.1.1.0-rc.2 = pre_release_lt  
    // - v2.2.0+foo <=> v2.2.0+bar = metadata_ne
    inline SemVerCompareResult semVerCompare(juce::String tag1, juce::String tag2, bool precise = false) {
        std::smatch matches1;
        std::smatch matches2;
        auto tag1_str = tag1.toStdString();
        auto tag2_str = tag2.toStdString();
        auto res1 = std::regex_match(tag1_str, matches1, intern::semver_regex_);
        auto res2 = std::regex_match(tag2_str, matches2, intern::semver_regex_);
        if(!(res1 && res2)) return invalid;

        if (precise) {
            // TODO: unimplemented
            jassertfalse;
            return invalid;
        }

        if (matches1[0] == matches2[0]) return eq;

        int major1 = std::stoi(matches1[1]);
        int major2 = std::stoi(matches2[1]);
        if (major1 < major2) return lt_breaking;
        if (major1 > major2) return gt_breaking;

        int minor1 = std::stoi(matches1[2]);
        int minor2 = std::stoi(matches2[2]);
        if (minor1 < minor2) return lt;
        if (minor1 > minor2) return gt;

        int patch1 = std::stoi(matches1[3]);
        int patch2 = std::stoi(matches2[3]);
        if (patch1 < patch2) return lt;
        if (patch1 > patch2) return gt;

        std::string pre_release_type1 = matches1[4].str();
        std::string pre_release_type2 = matches2[4].str();
        if (pre_release_type1.empty()) {
            if(!pre_release_type2.empty()) return gt;
            else return eq;
        }
        else if(pre_release_type2.empty()) return lt;
        if (pre_release_type1 == "a" && pre_release_type1 != pre_release_type2) return lt;
        if (pre_release_type1 == "b" && pre_release_type2 == "a") return gt;
        if (pre_release_type1 == "b" && pre_release_type2 == "rc") return lt;
        if (pre_release_type1 == "rc" && pre_release_type2 != pre_release_type1) return gt;

        int pr_patch1 = std::stoi(matches1[5]);
        int pr_patch2 = std::stoi(matches2[5]);
        if (pr_patch1 < pr_patch2) return lt;
        if (pr_patch1 > pr_patch2) return gt;

        // we checked for equality at the beginning, if you got here with no match, something is wrong
        jassertfalse;
        return invalid;
    }
}