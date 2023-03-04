/*
  ==============================================================================

    LevelMeter.h
    Created: 3 Mar 2023 6:24:19pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"


//==============================================================================
/*
*/
class LevelMeter  : public juce::Component, public Timer
{
public:
    LevelMeter(DJAudioPlayer* player);
    ~LevelMeter() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void setValue(float newValue);
    void setChannel(int channel);

    void updateValue();

    void timerCallback() override;


private:

    DJAudioPlayer* player;

    int channel;

    float decibles;
    float targetValue;
    float maxBarHeight;
    float barWidth;
    juce::Colour barColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};
