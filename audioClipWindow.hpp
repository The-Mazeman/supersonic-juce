#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_audio_utils/juce_audio_utils.h>

class AudioClipWindow : public juce::Component
{
    public:
    AudioClipWindow(std::unique_ptr<juce::AudioThumbnail> audioThumbnail);
    AudioClipWindow(AudioClipWindow&& other);

    private:
    void paint(juce::Graphics& graphics) override;
    std::unique_ptr<juce::AudioThumbnail> audioThumbnail;
};
