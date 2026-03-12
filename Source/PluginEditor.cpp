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
    juce::OpenGLHelpers::clear (juce::Colours::black);
    
    glEnable (GL_DEPTH_TEST);
    
    const float scale = (float) openGLContext.getRenderingScale();
    glViewport (0, 0, juce::roundToInt (getWidth() * scale), juce::roundToInt (getHeight() * scale));

    // Simple manual projection matrix to avoid gluPerspective
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    float farVal = 10.0f;
    float nearVal = 1.0f;
    float fov = 1.0f; // roughly 45 degrees
    float aspect = (float) getWidth() / (float) getHeight();
    glFrustum (-aspect * nearVal * fov, aspect * nearVal * fov, -nearVal * fov, nearVal * fov, nearVal, farVal);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0f, 0.0f, -4.0f);
    glRotatef (rotation, 0.2f, 1.0f, 0.3f);

    glColor3f (0.0f, 0.8f, 1.0f); // Neptune Blue
    drawSphere (1.3f, 15, 15);
        
    rotation += 0.8f;
}

void SphereVSTEditor::drawSphere (float radius, int slices, int stacks) {
    for (int i = 0; i <= stacks; ++i) {
        float lat0 = juce::MathConstants<float>::pi * (-0.5f + (float)(i - 1) / stacks);
        float z0 = radius * std::sin(lat0);
        float zr0 = radius * std::cos(lat0);

        float lat1 = juce::MathConstants<float>::pi * (-0.5f + (float)i / stacks);
        float z1 = radius * std::sin(lat1);
        float zr1 = radius * std::cos(lat1);

        glBegin (GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2.0f * juce::MathConstants<float>::pi * (float)(j - 1) / slices;
            float x = std::cos(lng);
            float y = std::sin(lng);
            glNormal3f (x * zr1, y * zr1, z1);
            glVertex3f (x * zr1, y * zr1, z1);
            glNormal3f (x * zr0, y * zr0, z0);
            glVertex3f (x * zr0, y * zr0, z0);
        }
        glEnd();
    }
}

void SphereVSTEditor::openGLContextClosing() {}
void SphereVSTEditor::paint (juce::Graphics& g) {}
void SphereVSTEditor::resized() {}