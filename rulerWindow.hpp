#include <juce_gui_basics/juce_gui_basics.h>
#include "globalSettings.hpp"

class RulerWindow : public juce::Component
{
    private:
    float multiplier;
    GlobalSettings* globalSettings;

    void paint(juce::Graphics& graphics) override;

    public:
    void setGlobalSettings(GlobalSettings* globalSettings);
};
