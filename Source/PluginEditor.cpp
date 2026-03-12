#include "PluginProcessor.h"
#include "PluginEditor.h"

// JUCE's safe way to get OpenGL headers across all platforms
#include <juce_opengl/native/juce_OpenGLHelpers.h>

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
    gluQuadricTexture (sphere, GL_TRUE);
    gluQuadricNormals (sphere, GLU_SMOOTH);

    auto img = juce::ImageFileFormat::loadFrom (BinaryData::texture_png, BinaryData::texture_pngSize);
    if (img.isValid())
        texture.loadImage (img);
}

void SphereVSTEditor::renderOpenGL() {
    juce::OpenGLHelpers::clear (juce::Colours::black);
    
    glEnable (GL_DEPTH_TEST);
    glEnable (GL_TEXTURE_2D);
    
    if (texture.getTextureID() > 0)
        texture.bind();

    const float scale = (float) openGLContext.getRenderingScale();
    glViewport (0, 0, juce::roundToInt (getWidth() * scale), juce::roundToInt (getHeight() * scale));

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45.0, (double) getWidth() / (double) getHeight(), 1.0, 10.0);

    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef (0.0f, 0.0f, -4.0f);
    glRotatef (rotation, 0.2f, 1.0f, 0.3f);

    if (sphere)
        gluSphere (sphere, 1.3, 60, 60);
        
    rotation += 0.8f;
}

void SphereVSTEditor::openGLContextClosing() {
    if (sphere) gluDeleteQuadric (sphere);
    texture.release();
}

void SphereVSTEditor::paint (juce::Graphics& g) {}
void SphereVSTEditor::resized() {}