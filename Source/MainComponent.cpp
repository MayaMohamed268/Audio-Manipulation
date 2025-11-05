#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(player);
    setSize(800, 480);
    setAudioChannels(0, 2); // no inputs, stereo output
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
    bufferToFill.clearActiveBufferRegion();
    player.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    player.releaseResources();
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

void MainComponent::resized()
{
    player.setBounds(getLocalBounds());
}
