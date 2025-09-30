#include "clipAreaWindow.hpp"

ClipAreaWindow::ClipAreaWindow()
    :audioThumbnailCache(1)
{
    audioFormatManager.registerBasicFormats();

}
void ClipAreaWindow::setGlobalSettings(GlobalSettings* globalSettings)
{
    this->globalSettings = globalSettings;
}
void ClipAreaWindow::paint(juce::Graphics& graphics)
{
    graphics.setColour(juce::Colours::darkgrey);
    auto bounds = getLocalBounds();
    graphics.drawRect(bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight());
#if 0

    float framesPerPixel = globalSettings->framesPerPixel;
    float sampleRate = globalSettings->sampleRate;
    float pixelsPerSecond = sampleRate / framesPerPixel;

    int markingCount = (int)((float)bounds.getWidth() / pixelsPerSecond);
    int offsetX = globalSettings->offsetX;
    offsetX *= -1;

    int markingStart = offsetX / pixelsPerSecond;
    for(int i = 0; i != markingCount + 2; ++i)
    {
        int offsetX = globalSettings->offsetX;
        int markingX = (pixelsPerSecond * (markingStart + i)) + offsetX;
        graphics.drawLine(markingX, 0, markingX, bounds.getHeight());
    }
#endif
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
        juce::String fileExtension = audioFile.getFileExtension();
        juce::AudioFormat* audioFormat = audioFormatManager.findFormatForFileExtension(fileExtension);
        if(!audioFormat)
        {
            std::cout << "FAILED: Cannot find audio format in audioFormatManager" << std::endl;
        }

        std::unique_ptr<juce::InputStream> inputStream = audioFile.createInputStream();
        juce::AudioFormatReader* audioFormatReader = audioFormat->createReaderFor(inputStream.get(), true);
        if(!audioFormatReader)
        {
            std::cout << "FAILED: Cannot create audioFormatReader from inputStream" << std::endl;
        }

        std::unique_ptr<juce::AudioThumbnail> audioThumbnail =  std::make_unique<juce::AudioThumbnail>(512, audioFormatManager, audioThumbnailCache);
        juce::FileInputSource* inputSource = new juce::FileInputSource(audioFile, true);
        audioThumbnail->setSource(inputSource);

        AudioClipWindow audioClipWindow = AudioClipWindow(std::move(audioThumbnail));
        audioClipWindow.setBounds(100, 100, 500, 200);

        addAndMakeVisible(audioClipWindow);
        audioClipWindows.push_back(std::move(audioClipWindow));
    }
}
