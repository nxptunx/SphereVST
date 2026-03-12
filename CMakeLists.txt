cmake_minimum_required(VERSION 3.15)
project(SphereVST VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(JUCE)

juce_add_plugin(SphereVST
    COMPANY_NAME "nxptunx"
    IS_SYNTH FALSE
    FORMATS VST3
    PRODUCT_NAME "SphereVST")

juce_generate_juce_header(SphereVST)

target_sources(SphereVST PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp)

target_link_libraries(SphereVST PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_gui_extra
    juce::juce_opengl
    $<$<PLATFORM_ID:Windows>:opengl32 glu32>
    $<$<PLATFORM_ID:Linux>:GL GLU>)