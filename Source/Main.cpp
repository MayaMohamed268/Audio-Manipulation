#include <JuceHeader.h>
#include "MainComponent.h"

<<<<<<< HEAD
<<<<<<< HEAD
class SimpleAudioPlayerApplication  : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override       { return "Simple Audio Player"; }
    const juce::String getApplicationVersion() override    { return "1.0"; }
    bool moreThanOneInstanceAllowed() override             { return true; }

    void initialise (const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow> (getApplicationName());
=======
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
>>>>>>> origin/main
    }

    void shutdown() override
    {
<<<<<<< HEAD
        mainWindow.reset();
=======
        mainWindow = nullptr;
>>>>>>> origin/main
    }

    void systemRequestedQuit() override
    {
        quit();
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
<<<<<<< HEAD
        MainWindow (juce::String name)
            : DocumentWindow (name,
                              juce::Colours::lightgrey,
                              DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
            setContentOwned (new MainComponent(), true);
            centreWithSize (800, 480);
            setVisible (true);
=======
class SimpleAudioPlayer : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Simple Audio Player"; }
    const juce::String getApplicationVersion() override { return "1.0"; }

    void initialise(const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override { mainWindow = nullptr; }

private:
    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name)
            : DocumentWindow(name, juce::Colours::darkgrey, DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);
            centreWithSize(750, 800);
            setVisible(true);
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
=======
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
>>>>>>> origin/main
        }

        void closeButtonPressed() override
        {
<<<<<<< HEAD
<<<<<<< HEAD
            JUCEApplication::getInstance()->systemRequestedQuit();
        }
=======
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
>>>>>>> origin/main
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

<<<<<<< HEAD
START_JUCE_APPLICATION (SimpleAudioPlayerApplication)
#include <JuceHeader.h>
#include "MainComponent.h"


START_JUCE_APPLICATION (SimpleAudioPlayerApplication)
=======
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(SimpleAudioPlayer)
>>>>>>> e6abad1e05246dfcff8840732eb2a63e70535a23
=======
<<<<<<< HEAD
START_JUCE_APPLICATION(SimpleAudioPlayerApplication)
=======
START_JUCE_APPLICATION(AudioAppApplication)
>>>>>>> new-feature
>>>>>>> origin/main
