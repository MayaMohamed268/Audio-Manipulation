<<<<<<< HEAD
﻿#include "PlayerAudio.h"
=======
#include "PlayerAudio.h"
>>>>>>> origin/main

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
}

<<<<<<< HEAD
PlayerAudio::~PlayerAudio() {}
=======
PlayerAudio::~PlayerAudio()
{
    transportSource.setSource(nullptr);
    readerSource.reset();
}

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (!file.existsAsFile())
        return false;

    if (auto* reader = formatManager.createReaderFor(file))
    {
        transportSource.stop();
        transportSource.setSource(nullptr);
        readerSource.reset();

        readerSource.reset(new juce::AudioFormatReaderSource(reader, true));
        transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
        transportSource.setPosition(0.0);
        transportSource.setGain(1.0f);

        
        title = reader->metadataValues.getValue("title", file.getFileName());
        artist = reader->metadataValues.getValue("artist", "Unknown Artist");
        album = reader->metadataValues.getValue("album", "Unknown Album");
        duration = (reader->lengthInSamples > 0 && reader->sampleRate > 0.0)
            ? (double)reader->lengthInSamples / reader->sampleRate
            : 0.0;

        return true;
    }

    return false;
}
>>>>>>> origin/main

void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
<<<<<<< HEAD
    transportSource.getNextAudioBlock(bufferToFill);
}

void PlayerAudio::stop()
{
    transportSource.stop();
=======
    if (readerSource)
        transportSource.getNextAudioBlock(bufferToFill);
    else
        bufferToFill.clearActiveBufferRegion();
>>>>>>> origin/main
}

void PlayerAudio::releaseResources()
{
    transportSource.releaseResources();
}

<<<<<<< HEAD
bool PlayerAudio::loadFile(const juce::File& file)
{
    if (file.existsAsFile())
    {
        if (auto* reader = formatManager.createReaderFor(file))
        {
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);
            transportSource.setSource(readerSource.get(), 0, nullptr, reader->sampleRate);
            transportSource.start(); 
        }
    }
    return true;
}

void PlayerAudio::play() { transportSource.start(); }

void PlayerAudio::pause() { transportSource.stop(); }

void PlayerAudio::goToStart() { transportSource.setPosition(0.0); }

void PlayerAudio::goToEnd() { transportSource.setPosition(transportSource.getLengthInSeconds()); }

void PlayerAudio::setGain(float gain) { transportSource.setGain(gain); }

void PlayerAudio::setPosition(double pos) { transportSource.setPosition(pos); }

double PlayerAudio::getPosition() const { return transportSource.getCurrentPosition(); }

double PlayerAudio::getLength() const { return transportSource.getLengthInSeconds(); }
=======
void PlayerAudio::play() { transportSource.start(); }
void PlayerAudio::pause() { transportSource.stop(); }
void PlayerAudio::stop() { transportSource.stop(); transportSource.setPosition(0.0); }
void PlayerAudio::goToStart() { transportSource.setPosition(0.0); }
void PlayerAudio::goToEnd()
{
    if (readerSource)
    {
        if (auto* r = readerSource->getAudioFormatReader())
        {
            double len = (double)r->lengthInSamples / r->sampleRate;
            transportSource.setPosition(len);
        }
    }
}

void PlayerAudio::setGain(float g)
{
    transportSource.setGain(g);
}

double PlayerAudio::getPosition() const { return transportSource.getCurrentPosition(); }
double PlayerAudio::getLength() const { return transportSource.getLengthInSeconds(); }
bool PlayerAudio::isPlaying() const { return transportSource.isPlaying(); }
>>>>>>> origin/main
