#include "audioClipWindow.hpp"

AudioClipWindow::AudioClipWindow(std::unique_ptr<juce::AudioThumbnail> audioThumbnail)
    :audioThumbnail(std::move(audioThumbnail))
{

}
AudioClipWindow::AudioClipWindow(AudioClipWindow&& other)
{
    this->audioThumbnail = std::move(other.audioThumbnail);
}
void AudioClipWindow::paint(juce::Graphics& graphics) 
{
    graphics.setColour(juce::Colours::white);
    graphics.fillRect(getLocalBounds());
    graphics.setColour(juce::Colours::red);
    if(audioThumbnail->isFullyLoaded())
    {
        auto clipLength = audioThumbnail->getTotalLength();
        audioThumbnail->drawChannels(graphics, getLocalBounds(), 0.0, clipLength, 1.0);
    }

}
