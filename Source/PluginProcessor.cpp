#include "PluginProcessor.h"
#include "PluginEditor.h"

juce::AudioProcessorEditor* SphereVSTAudioProcessor::createEditor() {
    return new SphereVSTEditor (*this);
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new SphereVSTAudioProcessor();
}