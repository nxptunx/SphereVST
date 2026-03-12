#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
// Fix for Windows OpenGL headers
#if JUCE_WINDOWS
 #include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

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
    juce::OpenGLTexture texture;
    float rotation = 0.0f;
    GLUquadric* sphere = nullptr;

    SphereVSTAudioProcessor& audioProcessor;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SphereVSTEditor)
};