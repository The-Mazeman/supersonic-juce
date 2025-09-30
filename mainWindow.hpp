#include <juce_gui_basics/juce_gui_basics.h>
#include "rulerWindow.hpp"
#include "trackHeaderAreaWindow.hpp"
#include "clipAreaWindow.hpp"
#include "globalSettings.hpp"

class MainWindow : public juce::DocumentWindow
{
    public:
    MainWindow();
    void resized() override;
    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& detail) override;

    private:
    GlobalSettings* globalSettings;
    RulerWindow rulerWindow;
    TrackHeaderAreaWindow trackHeaderAreaWindow;
    ClipAreaWindow clipAreaWindow;
};
