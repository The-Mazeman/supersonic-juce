#include "clipAreaWindow.hpp"

ClipAreaWindow::ClipAreaWindow()
    :audioThumbnailCache(1)
{
    this->multiplier = 1.0f;
    audioFormatManager.registerBasicFormats();

}
void ClipAreaWindow::setGlobalSettings(GlobalSettings* globalSettings)
{
    this->globalSettings = globalSettings;
}
void ClipAreaWindow::paint(juce::Graphics& graphics)
{
    graphics.setColour(juce::Colours::lightgrey);
    auto bounds = getLocalBounds();
    graphics.drawRect(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());

    graphics.setColour(juce::Colours::darkgrey);

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
        graphics.drawLine(markingX, 0, markingX, bounds.getHeight());

    }
}
bool ClipAreaWindow::isInterestedInDragSource(const SourceDetails& dragSourceDetails) 
{
    std::cout << "item is being dragged" << std::endl;
    return true;
}
void ClipAreaWindow::itemDropped(const SourceDetails& sourceDetails) 
{
}
bool ClipAreaWindow::isInterestedInFileDrag(const juce::StringArray& stringArray)
{
    return true;
}
void createAudioClipWindow(juce::String filePath, juce::AudioFormatManager audioFormatManager, AudioClipWindow& audioClipWindow)
{
}
void ClipAreaWindow::filesDropped(const juce::StringArray& stringArray, int x, int y)
{
    for (auto filePath: stringArray)
    {
        juce::File audioFile = juce::File(filePath.toRawUTF8());
        juce::AudioFormatReader* audioFormatReader = audioFormatManager.createReaderFor(audioFile);
        if(!audioFormatReader)
        {
            std::cout << "FAILED: Cannot create audioFormatReader from inputStream" << std::endl;
        }

        std::unique_ptr<juce::AudioThumbnail> audioThumbnail =  std::make_unique<juce::AudioThumbnail>(512, audioFormatManager, audioThumbnailCache);
        juce::FileInputSource* inputSource = new juce::FileInputSource(audioFile, true);
        audioThumbnail->setSource(inputSource);

        AudioClipWindow audioClipWindow = AudioClipWindow(std::move(audioThumbnail));
        double sampleCount = static_cast<double>(audioFormatReader->lengthInSamples);
        double framesPerPixel = static_cast<double>(globalSettings->framesPerPixel);
        int audioClipWidth = static_cast<int>(sampleCount / framesPerPixel);

        int trackHeaderHeight = globalSettings->trackHeaderHeight;
        audioClipWindow.setBounds(x, y, trackHeaderHeight, audioClipWidth);

        addAndMakeVisible(audioClipWindow);
        audioClipWindows.push_back(std::move(audioClipWindow));
    }
}
