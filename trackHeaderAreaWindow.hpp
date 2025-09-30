#include <juce_gui_basics/juce_gui_basics.h>
#include "globalSettings.hpp"

class TrackHeaderAreaWindow : public juce::Component
{
    private:
    GlobalSettings* globalSettings;

    void paint(juce::Graphics& graphics) override;

    public:
    void setGlobalSettings(GlobalSettings* globalSettings);
};
