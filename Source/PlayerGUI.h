#pragma once
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::ComboBox::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();
    void paint(juce::Graphics& g) override;
    void resized() override;
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;

private:
    PlayerAudio playerAudio;

    // Buttons
    juce::TextButton loadButton{ "Load File" }, restartButton{ "Restart" },
        stopButton{ "Stop" }, playButton{ "Play" },
        pauseButton{ "Pause" }, startButton{ "Go to Start" },
        endButton{ "Go to End" }, addButton{ "Add File" };

    // Volume & metadata
    juce::Slider volumeSlider;
    juce::Label metadataLabel;

    // Playlist
    juce::ComboBox playlistBox;
    std::vector<juce::File> playlistFiles;
    std::unique_ptr<juce::FileChooser> fileChooser;

    void loadSelectedFile(int index);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
