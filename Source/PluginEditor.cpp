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

void SphereVSTEditor::newOpenGLContextCreated() {
    sphere = gluNewQuadric();
    gluQuadricNormals (sphere, GLU_SMOOTH);
}

void SphereVSTEditor::renderOpenGL() {
    // Standard JUCE GL helper
    juce::OpenGLHelpers::clear (juce::Colours::black);
    
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_COLOR_MATERIAL);

    const float scale = (float) openGLContext.getRenderingScale();
    glViewport (0, 0, juce::roundToInt (getWidth() * scale), juce::roundToInt (getHeight() * scale));

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0, (double) getWidth() / (double) getHeight(), 1.0, 10.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0f, 0.0f, -4.0f);
    glRotatef (rotation, 0.2f, 1.0f, 0.3f);

    // Draw a wireframe sphere if GLU is working, otherwise a simple GL point
    if (sphere) {
        glColor3f(0.0f, 0.8f, 1.0f); // Neptune Blue
        gluSphere (sphere, 1.3, 20, 20);
    }
        
    rotation += 0.8f;
}

void SphereVSTEditor::openGLContextClosing() {
    if (sphere) gluDeleteQuadric (sphere);
}

void SphereVSTEditor::paint (juce::Graphics& g) {}
void SphereVSTEditor::resized() {}