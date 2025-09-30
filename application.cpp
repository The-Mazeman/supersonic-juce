#include "application.hpp"

void Application::initialise(const juce::String& commandLine) 
{
    mainWindow.reset(new MainWindow());
    mainWindow->setUsingNativeTitleBar(true);
    mainWindow->setResizable(true, false);
    mainWindow->centreWithSize(1400, 700);
    mainWindow->setVisible(true);
    mainWindow->setResizeLimits(200, 200, 3000, 3000);
    mainWindow->toFront(true);
    //dw->setBounds(0, 0, 400, 400);
}
void Application::shutdown() 
{
}
const juce::String Application::getApplicationName() 
{
    return "TEST";
}
const juce::String Application::getApplicationVersion() 
{
    return "1.0";
}
bool Application::perform(const InvocationInfo& info) 
{
    std::cout << "REsT" << std::endl;
    std::cout << info.commandID << std::endl;
    return false;
}
