#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"

class SphereVSTEditor : public juce::AudioProcessorEditor, public juce::OpenGLRenderer {
public:
    SphereVSTEditor (SphereVSTAudioProcessor&);
    ~SphereVSTEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void newOpenGLContextCreated() override;
    void renderOpenGL() override;
    void openGLContextClosing() override;

private:
    juce::OpenGLContext openGLContext;
    float rotation = 0.0f;

    // We'll use a simple JUCE-native way to draw the sphere 
    // to avoid the GLU header nightmare on Windows
    void drawSphere (float radius, int slices, int stacks);

    SphereVSTAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SphereVSTEditor)
};