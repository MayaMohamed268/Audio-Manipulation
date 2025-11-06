#pragma once
#include <JuceHeader.h>
#include "PlayerGUI.h"
<<<<<<< HEAD
=======
#include "../Builds/VisualStudio2022/PlayerGUI.h"
>>>>>>> new-feature

class MainComponent : public juce::AudioAppComponent
{
public:
    MainComponent();
    ~MainComponent() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
<<<<<<< HEAD
    PlayerGUI playerGui;
    juce::AudioDeviceManager audioDeviceManager;
=======
    PlayerGUI playerGUI;
>>>>>>> new-feature

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
