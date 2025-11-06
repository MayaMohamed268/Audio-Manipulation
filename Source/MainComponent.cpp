#include "MainComponent.h"

MainComponent::MainComponent()
{
<<<<<<< HEAD
    addAndMakeVisible(player);
<<<<<<< HEAD
    setSize(800, 480);
    setAudioChannels(0, 2); // no inputs, stereo output
=======
    setAudioChannels(0, 2);
    setSize(850, 900);
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
=======
<<<<<<< HEAD
    addAndMakeVisible(playerGui);
   



    setAudioChannels(0, 2);
=======
    addAndMakeVisible(playerGUI);
    setSize(920, 300);

    setAudioChannels(0, 2); // no inputs, 2 outputs
>>>>>>> new-feature
>>>>>>> origin/main
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
<<<<<<< HEAD
    player.prepareToPlay(samplesPerBlockExpected, sampleRate);
=======
<<<<<<< HEAD
    playerGui.prepareToPlay(samplesPerBlockExpected, sampleRate);
=======
    playerGUI.prepareToPlay(samplesPerBlockExpected, sampleRate);
>>>>>>> new-feature
>>>>>>> origin/main
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
<<<<<<< HEAD
<<<<<<< HEAD
    bufferToFill.clearActiveBufferRegion();
=======
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
    player.getNextAudioBlock(bufferToFill);
=======
    bufferToFill.clearActiveBufferRegion();
<<<<<<< HEAD
    playerGui.getNextAudioBlock(bufferToFill);
=======
    playerGUI.getNextAudioBlock(bufferToFill);
>>>>>>> new-feature
>>>>>>> origin/main
}

void MainComponent::releaseResources()
{
<<<<<<< HEAD
    player.releaseResources();
=======
<<<<<<< HEAD
    playerGui.releaseResources();
=======
    playerGUI.releaseResources();
>>>>>>> new-feature
>>>>>>> origin/main
}

void MainComponent::paint(juce::Graphics& g)
{
<<<<<<< HEAD
<<<<<<< HEAD
    g.fillAll(juce::Colours::darkgrey);
=======
    g.fillAll(juce::Colours::black);
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
=======
    g.fillAll(juce::Colours::black);
>>>>>>> origin/main
}

void MainComponent::resized()
{
<<<<<<< HEAD
    player.setBounds(getLocalBounds());
=======
<<<<<<< HEAD
    playerGui.setBounds(getLocalBounds());
=======
    playerGUI.setBounds(getLocalBounds());
>>>>>>> new-feature
>>>>>>> origin/main
}
