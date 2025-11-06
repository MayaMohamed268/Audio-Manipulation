#pragma once
#include <JuceHeader.h>

class PlayerAudio : public juce::AudioSource
{
public:
    PlayerAudio();
    ~PlayerAudio() override;

    bool loadFile(const juce::File& file);   
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    void play();
    void pause();
    void stop();
    void goToStart();
    void goToEnd();

    void setGain(float g);

    double getPosition() const;
    double getLength() const;
    bool isPlaying() const;

    juce::String getTitle() const { return title; }
    juce::String getArtist() const { return artist; }
    juce::String getAlbum() const { return album; }
    double getDuration() const { return duration; }

    juce::AudioFormatManager& getFormatManager() { return formatManager; }

private:
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    // metadata
    juce::String title{ "Unknown" };
    juce::String artist{ "Unknown" };
    juce::String album{ "Unknown" };
    double duration{ 0.0 };
};
