#include <JuceHeader.h>
#include "MainComponent.h"

class SimpleAudioPlayerApplication  : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override       { return "Simple Audio Player"; }
    const juce::String getApplicationVersion() override    { return "1.0"; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow> (getApplicationName());
    }

    void shutdown() override
    {
        mainWindow.reset();
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Colours::lightgrey,
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);
            centreWithSize (800, 480);
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION (SimpleAudioPlayerApplication)
#include <JuceHeader.h>
#include "MainComponent.h"


START_JUCE_APPLICATION (SimpleAudioPlayerApplication)
