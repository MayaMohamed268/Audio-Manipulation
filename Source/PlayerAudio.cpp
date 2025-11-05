#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();

    //جديد
    resampleSource = std::make_unique<juce::ResamplingAudioSource>(&transportSource, false, 2);
}

PlayerAudio::~PlayerAudio()
{
}
void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    //جديد 
    resampleSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    resampleSource->getNextAudioBlock(bufferToFill);//جدديد
    if (loopSegment)
    {
        double current = transportSource.getCurrentPosition();
        if (current >= loopEnd)
            transportSource.setPosition(loopStart);
    }

}
void PlayerAudio::releaseResources()
{
    resampleSource->releaseResources(); //جديد
}
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


            transportSource.setSource(readerSource.get(),
                0,
                nullptr,
                reader->sampleRate);


            title = reader->metadataValues.getValue("title", file.getFileName());
            artist = reader->metadataValues.getValue("artist", "Unknown Artist");
            album = reader->metadataValues.getValue("album", "Unknown Album");
            duration = reader->lengthInSamples / reader->sampleRate;

            transportSource.start();
        }
    }
    return true;

}
void PlayerAudio::play()
{
    transportSource.start();
}
void PlayerAudio::stop()
{
    transportSource.stop();
}
void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}
void PlayerAudio::setPosition(double pos) {
    transportSource.setPosition(pos);
}
double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}
double PlayerAudio::getLength() const
{
    return transportSource.getLengthInSeconds();
}
void PlayerAudio::toggleMute()
{
    if (!isMuted)
    {
        lastV = transportSource.getGain();
        transportSource.setGain(0.0f);
        isMuted = true;
    }
    else
    {
        transportSource.setGain(lastV);
        isMuted = false;
    }
}
void PlayerAudio::pause()
{
    transportSource.stop();
}
double PlayerAudio::getLengthInSeconds() const
{
    return transportSource.getLengthInSeconds();
}
void PlayerAudio::goToStart()
{
    transportSource.setPosition(0.0);
}
void PlayerAudio::goToEnd()
{
    auto len = transportSource.getLengthInSeconds();
    transportSource.setPosition(len);
}
void PlayerAudio::setLooping(bool shouldLoop)
{
    if (readerSource)
        readerSource->setLooping(shouldLoop);
}
void PlayerAudio::setSpeed(double newSpeed) //جدد
{
    if (resampleSource)
        resampleSource->setResamplingRatio(newSpeed);
}
void PlayerAudio::setLoopPoints(double start, double end)
{
    loopStart = start;
    loopEnd = end;
}

void PlayerAudio::enableLoop(bool shouldLoop)
{
    loopSegment = shouldLoop;
}

double PlayerAudio::getLoopStart() const
{
    return loopStart;
}

double PlayerAudio::getLoopEnd() const
{
    return loopEnd;
}
void PlayerAudio::setLoopSegmentEnabled(bool shouldLoop)
{
    loopSegment = shouldLoop;
}