#include <JuceHeader.h>
#include "MainComponent.h"

<<<<<<< HEAD
class SimpleAudioPlayerApplication : public juce::JUCEApplication
{
public:
    SimpleAudioPlayerApplication() {}
=======
class AudioAppApplication : public juce::JUCEApplication
{
public:
    AudioAppApplication() {}
>>>>>>> new-feature

    const juce::String getApplicationName() override { return "SimpleAudioPlayer"; }
    const juce::String getApplicationVersion() override { return "1.0"; }
    bool moreThanOneInstanceAllowed() override { return true; }

    void initialise(const juce::String&) override
    {
        mainWindow.reset(new MainWindow(getApplicationName()));
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name) : DocumentWindow(name,
<<<<<<< HEAD
            juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),
=======
            juce::Desktop::getInstance().getDefaultLookAndFeel()
            .findColour(ResizableWindow::backgroundColourId),
>>>>>>> new-feature
            DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);
<<<<<<< HEAD
            centreWithSize(720, 220);
=======
            centreWithSize(920, 300);
>>>>>>> new-feature
            setVisible(true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

<<<<<<< HEAD
START_JUCE_APPLICATION(SimpleAudioPlayerApplication)
=======
START_JUCE_APPLICATION(AudioAppApplication)
>>>>>>> new-feature
