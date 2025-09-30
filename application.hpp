#include <juce_gui_basics/juce_gui_basics.h>

#include "mainWindow.hpp"
class Application : public juce::JUCEApplication
{
    public:
        void initialise(const juce::String& commandLine) override;
        void shutdown() override;
        const juce::String getApplicationName() override;
        const juce::String getApplicationVersion() override;
        bool perform(const InvocationInfo& info) override;
    private:
        std::unique_ptr<MainWindow> mainWindow;
};
