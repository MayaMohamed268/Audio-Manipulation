#include <JuceHeader.h>
#include "MainComponent.h"

class MyApp : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Two Player Audio"; }
    const juce::String getApplicationVersion() override { return "1.0"; }

    void initialise(const juce::String&) override
    {
        mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr;
    }

    class MainWindow : public juce::DocumentWindow
    {
    public:
        MainWindow(juce::String name) :
            DocumentWindow(name, juce::Colours::darkgrey, allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);
            centreWithSize(1200, 400);
            setVisible(true);
        }

        void closeButtonPressed() override
        {
            juce::JUCEApplication::getInstance()->systemRequestedQuit();
        }
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

START_JUCE_APPLICATION(MyApp)