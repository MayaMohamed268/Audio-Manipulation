#include "MainComponent.h"

MainComponent::MainComponent()
{
<<<<<<< HEAD
    addAndMakeVisible(playerGui);
   



    setAudioChannels(0, 2);
=======
    addAndMakeVisible(playerGUI);
    setSize(920, 300);

    setAudioChannels(0, 2); // no inputs, 2 outputs
>>>>>>> new-feature
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
<<<<<<< HEAD
    playerGui.prepareToPlay(samplesPerBlockExpected, sampleRate);
=======
    playerGUI.prepareToPlay(samplesPerBlockExpected, sampleRate);
>>>>>>> new-feature
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    bufferToFill.clearActiveBufferRegion();
<<<<<<< HEAD
    playerGui.getNextAudioBlock(bufferToFill);
=======
    playerGUI.getNextAudioBlock(bufferToFill);
>>>>>>> new-feature
}

void MainComponent::releaseResources()
{
<<<<<<< HEAD
    playerGui.releaseResources();
=======
    playerGUI.releaseResources();
>>>>>>> new-feature
}

void MainComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void MainComponent::resized()
{
<<<<<<< HEAD
    playerGui.setBounds(getLocalBounds());
=======
    playerGUI.setBounds(getLocalBounds());
>>>>>>> new-feature
}
