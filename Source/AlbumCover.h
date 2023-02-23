/*
  ==============================================================================

    AlbumCover.h
    Created: 22 Feb 2023 10:16:01am
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AlbumCover  : public juce::Component
{
public:
    AlbumCover();
    ~AlbumCover() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AlbumCover)
};
