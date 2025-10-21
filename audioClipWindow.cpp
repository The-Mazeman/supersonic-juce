#include "audioClipWindow.hpp"

AudioClipWindow::AudioClipWindow(std::unique_ptr<juce::AudioThumbnail> audioThumbnail)
    :audioThumbnail(std::move(audioThumbnail))
{
    this->audioThumbnail->addChangeListener(this);

}
AudioClipWindow::AudioClipWindow(AudioClipWindow&& other)
{
    this->audioThumbnail = std::move(other.audioThumbnail);
    this->audioThumbnail->addChangeListener(this);
}
void AudioClipWindow::paint(juce::Graphics& graphics) 
{
    graphics.setColour(juce::Colours::black);
    graphics.fillRect(getLocalBounds());

    if(audioThumbnail->isFullyLoaded())
    {
        //std::cout << "PAINT" << std::endl;

        auto clipLength = audioThumbnail->getTotalLength();
        graphics.setColour(juce::Colours::white);
        audioThumbnail->drawChannels(graphics, getLocalBounds(), 0.0, clipLength, 1.0);
    }
}
void AudioClipWindow::changeListenerCallback(juce::ChangeBroadcaster* source)
{
    if(source == this->audioThumbnail.get())
    {
        std::cout << "Waveform data has been loaded !" << std::endl;
        repaint();
    }
}
void AudioClipWindow::mouseDown(const juce::MouseEvent& mouseEvent)
{
    auto position = mouseEvent.getPosition();
    mouseRelativeOffsetX = position.getX();
    mouseRelativeOffsetY = position.getY();
}
void AudioClipWindow::mouseDrag(const juce::MouseEvent& mouseEvent)
{
    auto parentComponent = getParentComponent();
    auto parentMouseEvent = mouseEvent.getEventRelativeTo(parentComponent);
    auto position = parentMouseEvent.getPosition();

    auto newX = position.getX() - mouseRelativeOffsetX;
    auto newY = position.getY() - mouseRelativeOffsetY;
    setTopLeftPosition({newX, newY});
}
