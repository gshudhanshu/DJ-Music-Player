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

    // Set the value of the level meter
	void setValue(float newValue);

    // Set the channel of the level meter
    void setChannel(int channel);

    // Update the value of the level meter
    void updateValue();

    // Timer callback for updating the recurring events
    void timerCallback() override;


private:

    DJAudioPlayer* player;

    int channel;

    juce::Colour barColour;

    float decibles;
    float targetValue;
    float maxBarHeight;
    float barWidth;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LevelMeter)
};
