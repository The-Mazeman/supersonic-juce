#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class AudioClipWindow : public juce::Component, public juce::ChangeListener
{
    public:
    AudioClipWindow(std::unique_ptr<juce::AudioThumbnail> audioThumbnail);
    AudioClipWindow(AudioClipWindow&& other);

    private:
    int mouseRelativeOffsetX;
    int mouseRelativeOffsetY;
    std::unique_ptr<juce::AudioThumbnail> audioThumbnail;

    void changeListenerCallback(juce::ChangeBroadcaster* source) override;
    void paint(juce::Graphics& graphics) override;
    void mouseDown(const juce::MouseEvent& mouseEvent) override;
    void mouseDrag(const juce::MouseEvent& mouseEvent) override;
};
