#pragma once
#include <JuceHeader.h>
#include "PlayerGUI.h"
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include "../Builds/VisualStudio2022/PlayerGUI.h"
>>>>>>> new-feature
>>>>>>> origin/main

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
<<<<<<< HEAD
<<<<<<< HEAD
    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    PlayerGUI player;

=======
    void resized() override;
    void paint(juce::Graphics& g) override;

private:
    PlayerGUI player;
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
=======

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
<<<<<<< HEAD
    PlayerGUI playerGui;
    juce::AudioDeviceManager audioDeviceManager;
=======
    PlayerGUI playerGUI;
>>>>>>> new-feature

>>>>>>> origin/main
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
