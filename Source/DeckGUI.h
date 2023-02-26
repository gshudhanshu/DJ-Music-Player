/*
  ==============================================================================

    DeckGUI.h
    Created: 13 Mar 2020 6:44:48pm
    Author:  matthew

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"

//==============================================================================
/*
*/
class DeckGUI    : public Component,
                   public Button::Listener, 
                   public Slider::Listener, 
                   public FileDragAndDropTarget, 
                   public Timer
{
public:
    DeckGUI(DJAudioPlayer* player,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

     /** implement Button::Listener */
    void buttonClicked (Button *) override;

    /** implement Slider::Listener */
    void sliderValueChanged (Slider *slider) override;

    bool isInterestedInFileDrag (const StringArray &files) override;
    void filesDropped (const StringArray &files, int x, int y) override; 

    void timerCallback() override; 
    void loadTrackToDeck(File file);

private:

    // Player buttons
    DrawableButton playButton{"PLAY", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton pauseButton{ "PAUSE", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton stopButton{"STOP", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton loopButton{ "LOOP", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton forwardButton{ "FORWARD", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton backwardButton{ "BACKWARD",DrawableButton::ButtonStyle::ImageOnButtonBackground };
    TextButton loadButton{ "LOAD" };
    

    String trackTitle;

    Slider volSlider; 
    Slider speedSlider;
    Slider posSlider;

    FileChooser fChooser{"Select a file..."};

    DJAudioPlayer* player;
    WaveformDisplay waveformDisplay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeckGUI)
};
