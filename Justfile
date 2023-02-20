set shell := ["bash", "-cu"]

setup:
    # go to JUCE directory
    cd {{JUCE_ROOT}}

    # Configure build with library components only
    cmake -B cmake-build-install -DCMAKE_INSTALL_PREFIX={{JUCE_ROOT}}
    
    # Run the installation
    cmake --build cmake-build-install --target install
