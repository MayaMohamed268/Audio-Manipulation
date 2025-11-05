#include <JuceHeader.h>
#include "MainComponent.h"

class MainApplication : public juce::JUCEApplication
{
public:
    const juce::String getApplicationName() override { return "Player"; }
    const juce::String getApplicationVersion() override { return "1.0"; }
    void initialise(const juce::String&) override { mainWindow.reset(new Window(*this)); }
    void shutdown() override { mainWindow = nullptr; }

    class Window : public juce::DocumentWindow
    {
    public:
        Window(JUCEApplication& a)
            : DocumentWindow("Player", juce::Colours::lightgrey, DocumentWindow::allButtons),
            app(a)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new MainComponent(), true);
            setResizable(false, false);
            centreWithSize(getWidth(), getHeight());
            setVisible(true);
        }
        void closeButtonPressed() override { app.systemRequestedQuit(); }
        JUCEApplication& app;
    };

private:
    std::unique_ptr<Window> mainWindow;
};

START_JUCE_APPLICATION(MainApplication)
