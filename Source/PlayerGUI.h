#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::AudioSource,
    public juce::Button::Listener,
    public juce::ComboBox::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;


    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;


    void paint(juce::Graphics& g) override;
    void resized() override;


    void buttonClicked(juce::Button* b) override;
    void comboBoxChanged(juce::ComboBox* cb) override;


    bool isPlaying() const;
    void stopPlayback();

private:
    PlayerAudio playerAudio;

    juce::TextButton loadButton{ "Load File" };
    juce::TextButton addButton{ "Add Files" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton pauseButton{ "Pause" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton startButton{ "Go to Start" };
    juce::TextButton endButton{ "Go to End" };
    juce::ComboBox playlistBox;
    std::vector<juce::File> playlistFiles;
    std::unique_ptr<juce::FileChooser> chooser;
    juce::Slider volumeSlider;
    juce::Label fileLabel{ {}, "No file" };

    void loadSelected(int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};