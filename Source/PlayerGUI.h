#pragma once
<<<<<<< HEAD
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::ComboBox::Listener,
    public juce::Slider::Listener
{
public:
    PlayerGUI();
    ~PlayerGUI() override;

  
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

  
    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* b) override;
    void comboBoxChanged(juce::ComboBox* cb) override;
    void sliderValueChanged(juce::Slider* s) override;

    
    bool isPlaying() const { return playerAudio.isPlaying(); }
    void stopPlayback() { playerAudio.stop(); }

private:
   
    PlayerAudio playerAudio;

    
    juce::TextButton loadButton{ "Load" };
    juce::TextButton addButton{ "Add" };
    juce::TextButton playButton{ "Play" };
    juce::TextButton pauseButton{ "Pause" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton startButton{ "Go to Start" };
    juce::TextButton endButton{ "Go to End" };
    //juce::AudioTransportSource& getTransport() { return playerAudio.getTransport(); }


    juce::Slider volumeSlider;  

    juce::Label infoLabel{ {}, "No file" };

   
    juce::ComboBox playlistBox;
    std::vector<juce::File> playlistFiles;
    std::unique_ptr<juce::FileChooser> chooser;

    void loadSelected(int index);
    void loadFile(const juce::File& f);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
=======
>>>>>>> new-feature
