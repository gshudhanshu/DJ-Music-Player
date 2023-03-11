/*
  ==============================================================================

    Header.h
    Created: 20 Feb 2023 6:16:28am
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class Header  : public juce::Component
{
public:
    Header();
    ~Header() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Header)
};
