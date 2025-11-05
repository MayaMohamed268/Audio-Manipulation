#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
    // Buttons
    for (auto* btn : { &loadButton, &restartButton, &stopButton,
                       &startButton, &pauseButton, &endButton, &playButton, &addButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume
    volumeSlider.setRange(0.0, 10.0, 0.1);
    volumeSlider.setValue(5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

    // Metadata label
    metadataLabel.setText("No file loaded", juce::dontSendNotification);
    metadataLabel.setJustificationType(juce::Justification::centred);
    metadataLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    metadataLabel.setFont(juce::Font(16.0f, juce::Font::bold));
    addAndMakeVisible(metadataLabel);

    // Playlist GUI
    addButton.addListener(this);
    addAndMakeVisible(addButton);
    addAndMakeVisible(playlistBox);
    playlistBox.addListener(this);
}

PlayerGUI::~PlayerGUI() {}

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
    metadataLabel.setText("Ready", juce::dontSendNotification);
}

void PlayerGUI::resized()
{
    int y = 60;
    loadButton.setBounds(40, y, 80, 40);
    playButton.setBounds(130, y, 80, 40);
    pauseButton.setBounds(220, y, 80, 40);
    stopButton.setBounds(310, y, 80, 40);
    restartButton.setBounds(400, y, 80, 40);
    startButton.setBounds(490, y, 80, 40);
    endButton.setBounds(580, y, 80, 40);

    metadataLabel.setBounds(10, 10, getWidth() - 20, 30);
    addButton.setBounds(20, 110, 120, 30);
    playlistBox.setBounds(160, 110, getWidth() - 180, 30);

    volumeSlider.setBounds(50, 160, getWidth() - 100, 20);
}

void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>("Select an audio file", juce::File{}, "*.mp3;*.wav");
        fileChooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& chooser)
            {
                auto file = chooser.getResult();
                if (file.existsAsFile())
                {
                    playerAudio.loadFile(file);
                    metadataLabel.setText("Loaded: " + file.getFileName(), juce::dontSendNotification);
                }
            });
    }

    if (button == &addButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select multiple audio files...", juce::File{}, "*.wav;*.mp3");

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

    if (button == &playButton) playerAudio.play();
    if (button == &pauseButton) playerAudio.pause();
    if (button == &stopButton) { playerAudio.stop(); playerAudio.setPosition(0.0); }
    if (button == &restartButton) playerAudio.goToStart();
    if (button == &startButton) playerAudio.goToStart();
    if (button == &endButton) playerAudio.goToEnd();
}

void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());
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
}
