#include "mainWindow.hpp"

MainWindow::MainWindow()
    :juce::DocumentWindow("test", juce::Colours::black, juce::DocumentWindow::TitleBarButtons::allButtons, true)
{
    GlobalSettings* globalSettings = new GlobalSettings;
    globalSettings->framesPerPixel = 512;
    globalSettings->sampleRate = 48000;

    this->globalSettings = globalSettings;
    
    rulerWindow.setGlobalSettings(globalSettings);
    trackHeaderAreaWindow.setGlobalSettings(globalSettings);
    clipAreaWindow.setGlobalSettings(globalSettings);
        

    addAndMakeVisible(rulerWindow);
    addAndMakeVisible(trackHeaderAreaWindow);
    addAndMakeVisible(clipAreaWindow);
}
void MainWindow::mouseWheelMove(const juce::MouseEvent& mouseEvent, const juce::MouseWheelDetails& detail)
{
    auto mouseEventInClipArea = mouseEvent.getEventRelativeTo(&clipAreaWindow);
    auto position = mouseEventInClipArea.position;
    float deltaX = detail.deltaX * 500.0;
    float deltaY = detail.deltaY * 500.0;

    float offsetX = static_cast<float>(globalSettings->offsetX);
    offsetX += deltaX;
    //std::cout << "offsetX: " << offsetX << std::endl;

    if(offsetX > 0.0)
    {
        offsetX = 0.0;
    }

    globalSettings->offsetX = static_cast<int>(offsetX);
    if(mouseEvent.mods.isCommandDown())
    {
        float deltaPercentage = deltaY / 100.0f;
        deltaPercentage *= -1;

        float framesPerPixel = globalSettings->framesPerPixel;
        float mousePositionX = position.getX() - offsetX;
        float mouseFrame = mousePositionX * framesPerPixel;
        framesPerPixel += (framesPerPixel * deltaPercentage);
        globalSettings->framesPerPixel = framesPerPixel;
        float newMousePositionX = mouseFrame / framesPerPixel;
        float mousePositionDeltaX = newMousePositionX - mousePositionX;
        std::cout << "mouseX: " << mousePositionX << std::endl;
        std::cout << "newMouseX: " << newMousePositionX << std::endl;
        std::cout << "mousePositionDeltaX: " << mousePositionDeltaX << std::endl;
        globalSettings->offsetX -= mousePositionDeltaX;
    }

    rulerWindow.repaint();
    clipAreaWindow.repaint();
}
void MainWindow::resized() 
{
    auto bounds = getLocalBounds();
    rulerWindow.setBounds(200, 0, bounds.getWidth() - 200, 32);
    trackHeaderAreaWindow.setBounds(0, 32, 200, bounds.getHeight() - 32);
    clipAreaWindow.setBounds(200, 32, bounds.getWidth() - 200, bounds.getHeight() - 32);
    
}
