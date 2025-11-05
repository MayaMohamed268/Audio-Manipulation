#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(player);
<<<<<<< HEAD
    setSize(800, 480);
    setAudioChannels(0, 2); // no inputs, stereo output
=======
    setAudioChannels(0, 2);
    setSize(850, 900);
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
<<<<<<< HEAD
    bufferToFill.clearActiveBufferRegion();
=======
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
    player.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
<<<<<<< HEAD
    g.fillAll(juce::Colours::darkgrey);
=======
    g.fillAll(juce::Colours::black);
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
}

void MainComponent::resized()
{
    player.setBounds(getLocalBounds());
}
