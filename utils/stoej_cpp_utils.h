/*
  ==============================================================================

    stoej_c_utils.h
    Created: 21 Jan 2023 1:15:03pm
    Author:  Lorenzo

  ==============================================================================
*/

#pragma once

namespace stoej {
    template<typename T>
    inline T ptr_or(T* ptr, T value) { return ptr ? *ptr : value; }
}