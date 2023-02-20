/*
  ==============================================================================

    stoej_APVTS.h
    Created: 20 Jan 2023 5:01:04pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "stoej_params.h"
#include "gui/stoej_Theming.h"
#include "utils/stoej_cpp_utils.h"
#include "stoej_properties.h"

namespace stoej {

    // basic extension to juce's APVTS to add some quality of life improvements
    // not necessary by any means, you can safely downcast and upcast to and from this and juce's APVTS
    class APVTS : public juce::AudioProcessorValueTreeState {
    public:
        APVTS(
            juce::AudioProcessor& processorToConnectTo,
            juce::UndoManager* undoManagerToUse,
            const juce::Identifier& valueTreeType,
            ParameterLayout parameterLayout
        ) : 
            juce::AudioProcessorValueTreeState(
                processorToConnectTo,
                undoManagerToUse,
                valueTreeType,
                std::move(parameterLayout)
            ) {}

        float getParameterFloat(stoej::FloatParamInfo info) {
            // TODO: adjust for skewness?
            auto maybe_val = this->getRawParameterValue(info.id);
            if (maybe_val) return maybe_val->load();
            else return info.init;
        }

        bool getParameterBool(stoej::BoolParamInfo info) {
            auto maybe_val = this->getRawParameterValue(info.id);
            if (maybe_val) return maybe_val->load() > 0.5f;
            else return info.init;
        }

        float getPropertyFloat(stoej::PropertyInfo info) {
            auto maybe_val = this->state.getProperty(info.id);
            if (maybe_val) return float(maybe_val);
            else return float(info.init);
        }

        void setPropertyFloat(stoej::PropertyInfo info, float val) {
            this->state.setProperty(info.id, val, nullptr);
        }

        bool getPropertyBool(stoej::PropertyInfo info) {
            auto maybe_val = this->state.getProperty(info.id);
            if (maybe_val) return bool(maybe_val);
            else return bool(info.init);
        }
    };

    // extension to APVTS to construct and access common internals. You should alwyas upcast to APVTS unless you
    // need access to the internals.
    // you can safely downcast to this to access internals
    class APVTSInternalsAccessor : public APVTS {
    public:
        using APVTS::getPropertyFloat;
        enum InternalParameterNames {};
        enum InternalPropertyNames {
            gui_scale,
        };
        using InternalFloatParameters = std::map<InternalParameterNames, FloatParamInfo>;
        using InternalBoolParameters = std::map<InternalParameterNames, BoolParamInfo>;
        using InternalProperties = std::map<InternalPropertyNames, PropertyInfo>;
        inline static const InternalFloatParameters internal_float_parameters = {};
        inline static const InternalBoolParameters internal_bool_parameters = {};
        inline static const InternalProperties internal_properties = {
            {gui_scale, {"Y0mDh-wQe8r6rXT6bA_QD", 2.0f}}
        };

        APVTSInternalsAccessor(
            juce::AudioProcessor& processorToConnectTo, 
            juce::UndoManager* undoManagerToUse, 
            const juce::Identifier& valueTreeType, 
            ParameterLayout parameterLayout
        ) 
        : 
        APVTS(
            processorToConnectTo,
            undoManagerToUse,
            valueTreeType,
            std::move(this->create_default_layout_helper(std::move(parameterLayout)))
        ) {
            for (auto const& [_, val] : this->internal_properties) {
                this->state.setProperty(val.id, val.init, nullptr);
            }
        }

        float getPropertyFloat(InternalPropertyNames name) {
            auto info = this->internal_properties.at(name);
            return this->getPropertyFloat(info);
        }

        void setPropertyFloat(InternalPropertyNames name, float val) {
            auto info = this->internal_properties.at(name);
            this->state.setProperty(info.id, val, nullptr);
        }

    private:
        
        static ParameterLayout create_default_layout_helper(ParameterLayout layout) {
            //for (auto const& [_, val] : internal_bool_parameters) {
            //    layout.add(create_unique_param_bool(val));
            //}
            //for (auto const& [_, val] : stoej::float_params) {
            //
            //}
            return layout;
        }
    };
}