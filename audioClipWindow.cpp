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
    std::cout << audioThumbnail->getTotalLength() << std::endl;
    audioThumbnail->drawChannels(graphics, getLocalBounds(), 0.0, audioThumbnail->getTotalLength(), 1.0);

}
