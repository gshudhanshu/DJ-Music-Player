/*
  ==============================================================================

    DiscArt.h
    Created: 2 Mar 2023 12:46:56pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class DiscArt  : public juce::Component
{
public:
    DiscArt();
    ~DiscArt() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiscArt)
};
