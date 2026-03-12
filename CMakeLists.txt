cmake_minimum_required(VERSION 3.15)
project(SphereVST VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(JUCE)

juce_add_plugin(SphereVST
    COMPANY_NAME "nxptunx"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    FORMATS VST3
    PRODUCT_NAME "SphereVST")

# This line turns your PNG into C++ code automatically
juce_add_binary_data(SphereData SOURCES Resources/texture.png)

juce_generate_juce_header(SphereVST)

target_sources(SphereVST PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

target_compile_definitions(SphereVST PUBLIC
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0)

target_link_libraries(SphereVST PRIVATE
    SphereData
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_gui_extra
    juce::juce_opengl
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    # Cross-platform GL linking
    $<$<PLATFORM_ID:Windows>:opengl32 glu32>
    $<$<PLATFORM_ID:Linux>:GL GLU>)