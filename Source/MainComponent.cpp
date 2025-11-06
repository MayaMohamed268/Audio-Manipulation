#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(playerGui);
   



    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerGui.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
    playerGui.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    playerGui.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
    playerGui.setBounds(getLocalBounds());
}
