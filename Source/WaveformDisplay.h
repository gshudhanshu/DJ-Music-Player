/*
  ==============================================================================

    WaveformDisplay.h
    Created: 14 Mar 2020 3:50:16pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "DJAudioPlayer.h"
#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WaveformDisplay    : public Component, 
                           public ChangeListener
{
public:
    WaveformDisplay( AudioFormatManager & 	formatManagerToUse,
                    AudioThumbnailCache & 	cacheToUse, Colour &playerColour);
    ~WaveformDisplay();

    void paint (Graphics&) override;
    void resized() override;

    // Change listener callback for updating the waveform display
    void changeListenerCallback (ChangeBroadcaster *source) override;

    // Load the audio file to the waveform display
    void loadURL(URL audioURL);

    // set the relative position of the playhead
    void setPositionRelative(double pos);

	// get the relative position of the mouse
    float getMousePosition();

private:
    AudioThumbnail audioThumb;
    bool fileLoaded; 
    double position;
    Colour* playerColour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
