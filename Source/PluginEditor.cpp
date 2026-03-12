#include "PluginProcessor.h"
#include "PluginEditor.h"

SphereVSTEditor::SphereVSTEditor (SphereVSTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (500, 500);
    openGLContext.setRenderer (this);
    openGLContext.setContinuousRepainting (true);
    openGLContext.attachTo (*this);
}

SphereVSTEditor::~SphereVSTEditor() {
    openGLContext.detach();
}

void SphereVSTEditor::newOpenGLContextCreated() {}

void SphereVSTEditor::renderOpenGL() {
    // This helper clears the background without needing raw GL calls
    juce::OpenGLHelpers::clear (juce::Colours::black);
    
    // We get the function table from JUCE so we don't need to include <GL/gl.h>
    auto& g = openGLContext.extensions;

    // If the context isn't ready, stop here
    if (! openGLContext.isActive()) return;

    // Use JUCE's internal GL function wrappers
    glEnable (0x0B71); // GL_DEPTH_TEST hex code to avoid header dependency
    
    const float scale = (float) openGLContext.getRenderingScale();
    glViewport (0, 0, juce::roundToInt (getWidth() * scale), juce::roundToInt (getHeight() * scale));

    glMatrixMode (0x1701); // GL_PROJECTION
    glLoadIdentity();
    
    glMatrixMode (0x1700); // GL_MODELVIEW
    glLoadIdentity();
    glTranslatef (0.0f, 0.0f, -0.5f);
    glRotatef (rotation, 0.0f, 1.0f, 0.5f);

    // Draw a simple triangle just to prove the build works
    glBegin (0x0004); // GL_TRIANGLES
        glColor3f (0.0f, 0.8f, 1.0f); // Neptune Blue
        glVertex3f ( 0.0f,  0.2f, 0.0f);
        glVertex3f (-0.2f, -0.2f, 0.0f);
        glVertex3f ( 0.2f, -0.2f, 0.0f);
    glEnd();
        
    rotation += 2.0f;
}

void SphereVSTEditor::openGLContextClosing() {}
void SphereVSTEditor::paint (juce::Graphics& g) {}
void SphereVSTEditor::resized() {}