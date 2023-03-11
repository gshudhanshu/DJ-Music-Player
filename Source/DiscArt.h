/*
  ==============================================================================

    DiscArt.h
    Created: 2 Mar 2023 12:46:56pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"

//==============================================================================
/*
*/
class DiscArt  : public juce::Component, public juce::Timer
{
public:
    DiscArt(DJAudioPlayer* player);
    ~DiscArt() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    // Timer callback for updating the recurring events
    void timerCallback();

    // Set the disc color
    void setDiscColour(Colour newColour);
    // Set the rotation speed
    void setRotationSpeed(float newSpeed);

private:
    DJAudioPlayer* player;
    Colour primaryColor;

    float rotationAngle = 0.0f;
    float rotationSpeed = 0.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiscArt)
};
