#include "PlayerGUI.h"

void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}

void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}

void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);

    if (fileLoaded)
    {
        g.setColour(juce::Colours::lightblue);
        thumbnail.drawChannels(g, getLocalBounds(), 0.0, thumbnail.getTotalLength(), 1.0f);

        // المؤشر الأحمر
        double position = playerAudio.getPosition();
        double length = playerAudio.getLength();
        if (length > 0)
        {
            float x = (position / length) * getWidth();
            g.setColour(juce::Colours::red);
            g.drawLine(x, 0.0f, x, (float)getHeight(), 2.0f);
        }
    }
    else
    {
        g.setColour(juce::Colours::white);
        g.drawFittedText("No file loaded", getLocalBounds(), juce::Justification::centred, 1);
    }

    juce::ColourGradient gradient(
        juce::Colour::fromRGB(10, 30, 60), 0, 0,
        juce::Colour::fromRGB(0, 10, 30), getWidth(), getHeight(),
        false
    );

    g.setGradientFill(gradient);
    g.fillAll();

    // خط فاصل ناعم بلون أزرق فاتح
    g.setColour(juce::Colours::skyblue.withAlpha(0.5f));
    g.drawLine(20, 90, getWidth() - 20, 90, 1.5f);


    g.setColour(juce::Colours::skyblue);
    auto waveformArea = getLocalBounds().reduced(20, 120);

    if (thumbnail.getNumChannels() > 0)
    {
        thumbnail.drawChannels(g, waveformArea, 0.0, playerAudio.getLength(), 1.0f);

        // Pointer
        double positionX = waveformArea.getX() + (playerAudio.getPosition() / playerAudio.getLength()) * waveformArea.getWidth();
        g.setColour(juce::Colours::yellow);
        g.drawLine((float)positionX, waveformArea.getY(), (float)positionX, waveformArea.getBottom(), 2.0f);
    }
    else
    {
        g.setColour(juce::Colours::white);
        g.drawFittedText("No waveform loaded", waveformArea, juce::Justification::centred, 1);
    }
}


PlayerGUI::PlayerGUI()
{
    // Add buttons
    for (auto* btn : { &loadButton, &restartButton, &stopButton, &muteButton,
                       &startButton, &pauseButton, &endButton, &loopButton, &playButton ,&addButton })
    {
        btn->addListener(this);
        metadataLabel.setColour(juce::Label::textColourId, juce::Colours::lightblue);
        addAndMakeVisible(btn);

    }

    // Volume
    volumeSlider.setRange(0.0, 10.0, 0.1);
    volumeSlider.setValue(5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // Speed
    speedSlider.setRange(0.5, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);

    positionSlider.setColour(juce::Slider::thumbColourId, juce::Colours::deepskyblue);
    positionSlider.setColour(juce::Slider::trackColourId, juce::Colours::lightblue);

    volumeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::dodgerblue);
    speedSlider.setColour(juce::Slider::thumbColourId, juce::Colours::cornflowerblue);

    // Position
    positionSlider.setRange(0.0, 1.0, 0.001);
    positionSlider.addListener(this);
    addAndMakeVisible(positionSlider);


    positionLabel.setText("0.0 / 0.0 sec", juce::dontSendNotification);
    positionLabel.setJustificationType(juce::Justification::centred);
    positionLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible(positionLabel);

    thumbnail.addChangeListener(this);
    metadataLabel.setText("No file loaded", juce::dontSendNotification);
    metadataLabel.setJustificationType(juce::Justification::centred);
    metadataLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    metadataLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    addAndMakeVisible(metadataLabel);

    // Playlist GUI
    addAndMakeVisible(addButton);
    addButton.addListener(this);
    addAndMakeVisible(playlistBox);
    playlistBox.addListener(this);

    // Timer
    startTimerHz(10);

    formatManager.registerBasicFormats();
    thumbnail.addChangeListener(this);
    startTimerHz(30);

    addAndMakeVisible(setAButton);
    setAButton.onClick = [this] {
        playerAudio.setLoopPoints(playerAudio.getPosition(), playerAudio.getLength()); // مؤقت
        };

    addAndMakeVisible(setBButton);
    setBButton.onClick = [this] {
        double start = playerAudio.getLoopStart();
        playerAudio.setLoopPoints(start, playerAudio.getPosition());
        };

    addAndMakeVisible(loopABButton);
    loopABButton.onClick = [this] {
        playerAudio.setLoopSegmentEnabled(loopABButton.getToggleState());
        };
    auto styleButton = [](juce::TextButton& b, juce::Colour c)
        {
            b.setColour(juce::TextButton::buttonColourId, c);
            b.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
            b.setColour(juce::TextButton::buttonOnColourId, c.brighter(0.2f));
        };
    styleButton(loadButton, juce::Colour::fromRGB(0, 102, 204));   // Blue
    styleButton(playButton, juce::Colour::fromRGB(0, 153, 255));   // Sky blue
    styleButton(pauseButton, juce::Colour::fromRGB(0, 128, 255));  // Mid blue
    styleButton(stopButton, juce::Colour::fromRGB(0, 51, 153));    // Deep blue
    styleButton(loopButton, juce::Colour::fromRGB(0, 204, 255));   // Cyan blue

}

void PlayerGUI::resized()
{
    int y = 60;
    loadButton.setBounds(40, y, 80, 40);
    restartButton.setBounds(130, y, 80, 40);
    stopButton.setBounds(220, y, 80, 40);
    muteButton.setBounds(310, y, 80, 40);
    loopButton.setBounds(400, y, 80, 40);
    playButton.setBounds(490, y, 80, 40);
    pauseButton.setBounds(580, y, 80, 40);
    startButton.setBounds(670, y, 60, 40);
    endButton.setBounds(740, y, 60, 40);

    metadataLabel.setBounds(10, 10, getWidth() - 20, 30);
    addButton.setBounds(20, 110, 120, 30);
    playlistBox.setBounds(160, 110, getWidth() - 180, 30);

    volumeSlider.setBounds(50, 160, getWidth() - 100, 20);
    speedSlider.setBounds(50, 190, getWidth() - 100, 20);
    positionSlider.setBounds(50, 220, getWidth() - 100, 20);
    positionLabel.setBounds(50, 245, getWidth() - 100, 20);

    setAButton.setBounds(10, 255, 60, 25);
    setBButton.setBounds(80, 255, 60, 25);
    loopABButton.setBounds(150, 255, 80, 25);


}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    // 🔹 Load single file
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>("Select an audio file", juce::File{}, ".mp3;.wav");
        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& chooser)
            {
                auto file = chooser.getResult();
                if (file.existsAsFile())
                {
                    playerAudio.loadFile(file);
                    thumbnail.setSource(new juce::FileInputSource(file));
                    fileLoaded = true;
                    repaint();



                    juce::AudioFormatManager formatManager;
                    formatManager.registerBasicFormats();

                    if (auto* reader = formatManager.createReaderFor(file))
                    {
                        juce::String title = reader->metadataValues.getValue("title", "");
                        juce::String artist = reader->metadataValues.getValue("artist", "");
                        juce::String duration = juce::String(reader->lengthInSamples / reader->sampleRate, 2) + " sec";

                        if (title.isNotEmpty() || artist.isNotEmpty())
                        {
                            metadataLabel.setText("the song is " + title + " - " + artist + " (" + duration + ")", juce::dontSendNotification);
                        }
                        else
                        {
                            metadataLabel.setText("the file is " + file.getFileName() + " (" + duration + ")", juce::dontSendNotification);
                        }

                        delete reader;
                    }

                }

            });
    }

    // 🔹 Playlist add multiple files
    if (button == &addButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select multiple audio files...", juce::File{}, ".wav;.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser& chooser)
            {
                auto results = chooser.getResults();
                for (auto& file : results)
                {
                    playlistFiles.push_back(file);
                    playlistBox.addItem(file.getFileName(), playlistBox.getNumItems() + 1);
                }
                if (!results.isEmpty())
                {
                    playlistBox.setSelectedId(1);
                    loadSelectedFile(0);
                }
            });
    }

    // 🔹 Playback controls
    if (button == &playButton) playerAudio.play();
    if (button == &pauseButton) playerAudio.pause();
    if (button == &stopButton) { playerAudio.stop(); playerAudio.setPosition(0.0); }
    if (button == &restartButton) playerAudio.goToStart();
    if (button == &startButton) playerAudio.goToStart();
    if (button == &endButton) playerAudio.goToEnd();

    // 🔹 Mute toggle
    if (button == &muteButton)
    {
        playerAudio.toggleMute();

        if (playerAudio.isMuted)
        {
            muteButton.setButtonText("unmute");
            muteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
        }
        else
        {
            muteButton.setButtonText("mute");
            muteButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
        }
    }

    // 🔹 Loop toggle
    if (button == &loopButton)
    {
        isLooping = !isLooping;
        playerAudio.setLooping(isLooping);

        if (isLooping)
        {
            loopButton.setButtonText("Looping");
            loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::lightblue);
        }
        else
        {
            loopButton.setButtonText("Loop");
            loopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::grey);
        }
    }
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());

    if (slider == &speedSlider)
        playerAudio.setSpeed(speedSlider.getValue());

    if (slider == &positionSlider)
    {
        if (playerAudio.getLength() > 0)
        {
            double pos = positionSlider.getValue() * playerAudio.getLength();
            playerAudio.setPosition(pos);
        }
    }
}

void PlayerGUI::timerCallback()
{
    double pos = playerAudio.getPosition();
    double len = playerAudio.getLength();

    if (len > 0)
    {
        positionSlider.setValue(pos / len, juce::dontSendNotification);
        positionLabel.setText(
            juce::String(pos, 2) + " / " + juce::String(len, 2) + " sec",
            juce::dontSendNotification);
    }

    repaint();
}


void PlayerGUI::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &playlistBox)
    {
        int index = comboBox->getSelectedId() - 1;
        loadSelectedFile(index);
    }
}

void PlayerGUI::loadSelectedFile(int index)
{
    if (index < 0 || index >= (int)playlistFiles.size())
        return;

    auto file = playlistFiles[index];
    if (playerAudio.loadFile(file))
        metadataLabel.setText("Playing: " + file.getFileName(), juce::dontSendNotification);

    thumbnail.setSource(new juce::FileInputSource(file));
}

PlayerGUI::~PlayerGUI()
{
    stopTimer();
}
void PlayerGUI::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if (source == &thumbnail)
        repaint(); // عشان نرسم الموجة لما تتحدث
}
void PlayerGUI::mouseDown(const juce::MouseEvent& event)
{
    if (fileLoaded)
    {
        double ratio = (double)event.x / getWidth();
        double newPosition = ratio * playerAudio.getLength();
        playerAudio.setPosition(newPosition);
    }
}

void PlayerGUI::mouseDrag(const juce::MouseEvent& event)
{
    if (fileLoaded)
    {
        double ratio = (double)event.x / getWidth();
        double newPosition = ratio * playerAudio.getLength();
        playerAudio.setPosition(newPosition);
    }
}