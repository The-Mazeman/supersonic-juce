#include "trackHeaderAreaWindow.hpp"

void TrackHeaderAreaWindow::setGlobalSettings(GlobalSettings* globalSettings)
{
    this->globalSettings = globalSettings;
}
void TrackHeaderAreaWindow::paint(juce::Graphics& graphics)
{
    graphics.setColour(juce::Colours::lightgrey);
    auto bounds = getLocalBounds();
    graphics.drawRect(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
}
