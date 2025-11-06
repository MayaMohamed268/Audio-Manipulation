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
    g.fillAll(juce::Colours::darkslategrey);
    g.setColour(juce::Colours::white);
    g.setFont(14.0f);
    g.drawText(infoLabel.getText(), 8, 6, getWidth() - 16, 20, juce::Justification::left);
}

void PlayerGUI::resized()
{
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
