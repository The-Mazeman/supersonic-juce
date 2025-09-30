#include <juce_gui_basics/juce_gui_basics.h>
#include "globalSettings.hpp"
#include "audioClipWindow.hpp"

class ClipAreaWindow : public juce::Component, 
                       public juce::DragAndDropTarget,
                       public juce::FileDragAndDropTarget
{
    private:
    GlobalSettings* globalSettings;
    std::vector<AudioClipWindow> audioClipWindows;
    juce::AudioThumbnailCache audioThumbnailCache;
    juce::AudioFormatManager audioFormatManager;

    void paint(juce::Graphics& graphics) override;

    public:
    ClipAreaWindow();

    void setGlobalSettings(GlobalSettings* globalSettings);
    bool isInterestedInFileDrag(const juce::StringArray& stringArray) override;
    void filesDropped(const juce::StringArray& stringArray, int x, int y) override;
    bool isInterestedInDragSource (const SourceDetails& dragSourceDetails) override;
    void itemDropped(const SourceDetails& sourceDetails) override;
};
