<<<<<<< HEAD
ï»¿#include "PlayerGUI.h"

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
=======
#include "PlayerGUI.h"

PlayerGUI::PlayerGUI()
{
   
    for (auto* b : { &loadButton, &addButton, &playButton, &pauseButton, &stopButton, &startButton, &endButton })
    {
        addAndMakeVisible(b);
        b->addListener(this);
    }

    addAndMakeVisible(volumeSlider);
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(1.0);
    volumeSlider.addListener(this);
    volumeSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 60, 20);

    addAndMakeVisible(infoLabel);
    infoLabel.setJustificationType(juce::Justification::centredLeft);

    addAndMakeVisible(playlistBox);
    playlistBox.addListener(this);

    setSize(700, 180);
}

PlayerGUI::~PlayerGUI()
{
}
>>>>>>> origin/main

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
<<<<<<< HEAD
    g.fillAll(juce::Colours::black);
    metadataLabel.setText("Ready", juce::dontSendNotification);
=======
    g.fillAll(juce::Colours::darkslategrey);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText(infoLabel.getText(), 8, 6, getWidth() - 16, 20, juce::Justification::left);
>>>>>>> origin/main
}

void PlayerGUI::resized()
{
<<<<<<< HEAD
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
=======
    auto area = getLocalBounds().reduced(8);
    auto row = area.removeFromTop(28);

    loadButton.setBounds(row.removeFromLeft(70));
    addButton.setBounds(row.removeFromLeft(60));
    playButton.setBounds(row.removeFromLeft(70));
    pauseButton.setBounds(row.removeFromLeft(70));
    stopButton.setBounds(row.removeFromLeft(60));
    startButton.setBounds(row.removeFromLeft(100));
    endButton.setBounds(row.removeFromLeft(80));

    auto bottom = area.removeFromTop(40);
    playlistBox.setBounds(bottom.removeFromLeft(getWidth() - 220));
    volumeSlider.setBounds(bottom.removeFromRight(200).reduced(4));
}

void PlayerGUI::buttonClicked(juce::Button* b)
{
    if (b == &loadButton)
    {
        chooser.reset(new juce::FileChooser("Select audio file", {}, "*.wav;*.mp3;*.flac"));
        chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles,
            [this](const juce::FileChooser& fc)
            {
                auto f = fc.getResult();
                if (f.existsAsFile())
                    loadFile(f);
            });
    }
    else if (b == &addButton)
    {
        chooser.reset(new juce::FileChooser("Add multiple files", {}, "*.wav;*.mp3;*.flac"));
        chooser->launchAsync(juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser& fc)
            {
                auto list = fc.getResults();
                for (auto& f : list)
                {
                    playlistFiles.push_back(f);
                    playlistBox.addItem(f.getFileName(), playlistBox.getNumItems() + 1);
                }

                if (!playlistFiles.empty() && playlistBox.getNumItems() > 0)
                    playlistBox.setSelectedId(1);
            });
    }
    else if (b == &playButton)  playerAudio.play();
    else if (b == &pauseButton) playerAudio.pause();
    else if (b == &stopButton) { playerAudio.stop(); playerAudio.goToStart(); }
    else if (b == &startButton) playerAudio.goToStart();
    else if (b == &endButton)   playerAudio.goToEnd();
}

void PlayerGUI::comboBoxChanged(juce::ComboBox* cb)
{
    if (cb == &playlistBox)
        loadSelected(cb->getSelectedId() - 1);
}

void PlayerGUI::sliderValueChanged(juce::Slider* s)
{
    if (s == &volumeSlider)
        playerAudio.setGain((float)volumeSlider.getValue());
}

void PlayerGUI::loadSelected(int index)
{
    if (index < 0 || index >= (int)playlistFiles.size()) return;
    loadFile(playlistFiles[index]);
}

void PlayerGUI::loadFile(const juce::File& f)
{
    if (playerAudio.loadFile(f))
    {
        infoLabel.setText(f.getFileName() + "  —  " + playerAudio.getArtist() + " - " + playerAudio.getTitle()
            + " (" + juce::String(playerAudio.getDuration(), 2) + "s)", juce::dontSendNotification);

        // ensure playlist box shows file
        bool found = false;
        for (int i = 1; i <= playlistBox.getNumItems(); ++i)
        {
            if (playlistBox.getItemText(i) == f.getFileName())
            {
                playlistBox.setSelectedId(i);
                found = true;
                break;
            }
        }
        if (!found)
        {
            playlistFiles.push_back(f);
            playlistBox.addItem(f.getFileName(), playlistBox.getNumItems() + 1);
            playlistBox.setSelectedId(playlistBox.getNumItems());
        }
    }
}
>>>>>>> origin/main
