#include "rulerWindow.hpp"

void RulerWindow::setGlobalSettings(GlobalSettings* globalSettings)
{
    this->multiplier = 1.0f;
    this->globalSettings = globalSettings;
}
void RulerWindow::paint(juce::Graphics& graphics)
{
    graphics.setColour(juce::Colours::lightgrey);
    auto bounds = getLocalBounds();
    graphics.drawRect(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());

    float framesPerPixel = globalSettings->framesPerPixel;
    float sampleRate = globalSettings->sampleRate;
    float pixelsPerSecond = sampleRate / framesPerPixel;
    if(pixelsPerSecond * multiplier < 128.0f)
    {
        multiplier *= 2.0f;
    }
    else if(pixelsPerSecond * multiplier > 256.0f)
    {
        multiplier /= 2.0f;
    }

    pixelsPerSecond *= multiplier;
    //std::cout << "pixelsPerSecond: " << pixelsPerSecond << std::endl;
    int markingCount = static_cast<int>(static_cast<float>(bounds.getWidth()) / pixelsPerSecond);

    for(int i = 0; i != markingCount + 2; ++i)
    {
        int offsetX = globalSettings->offsetX * -1;
        int markingStart = offsetX / pixelsPerSecond;
        int markingX = (pixelsPerSecond * (markingStart + i)) - offsetX;
        graphics.drawLine(markingX, 0, markingX, 16);

        float markingNumber = static_cast<float>(i + markingStart);
        markingNumber *= multiplier;

        juce::AttributedString markingString = juce::AttributedString(juce::String(markingNumber));
        markingString.setColour(juce::Colours::lightgrey);

        juce::Font currentFont = graphics.getCurrentFont();
        markingString.setFont(currentFont);

        juce::TextLayout textLayout = {};
        textLayout.createLayout(markingString, 200);

        float stringWidth = textLayout.getWidth();
        float stringHeight = textLayout.getHeight();
        auto stringBound = juce::Rectangle(static_cast<float>(markingX), 16.0f, stringWidth, stringHeight);
        textLayout.draw(graphics, stringBound);
    }
}
