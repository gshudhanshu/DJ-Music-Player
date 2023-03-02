/*
  ==============================================================================

    VolumeMeter.h
    Created: 2 Mar 2023 12:45:08pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

//==============================================================================
/*
 Taken reference from youtube www.youtube.com/watch?v=ILMdPjFQ9ps&t
*/
class VolumeMeter  : public juce::Component, public Timer
{
public:
    VolumeMeter(AudioFormatManager& formatManagerToUse,
        AudioThumbnailCache& cacheToUse);
    ~VolumeMeter() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void timerCallback()override;

private:
    std::function<float()> valueSupplier;
    ColourGradient gradient{};
    Image overlayGrill;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeMeter)
};
