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
#include "LevelMeter.h"
#include "DiscArt.h"
#include "MyLookAndFeel.h"

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
    DeckGUI(DJAudioPlayer* player, String* side,
            juce::AudioFormatManager & formatManagerToUse,
            juce::AudioThumbnailCache & cacheToUse);
    ~DeckGUI();

    void paint (Graphics&) override;
    void resized() override;

    // Button click events for all the buttons
    void buttonClicked (Button *) override;

    // Slider value change events for all the sliders
    void sliderValueChanged (Slider *slider) override;

    // Mouse click event for waveform display
    void mouseDown(const MouseEvent& event) override;

    // File drag and drop events
    bool isInterestedInFileDrag (const StringArray &files) override;

    // File dropped event for loading the track
	void filesDropped (const StringArray &files, int x, int y) override; 

    // Timer callback for updating the recurring events
    void timerCallback() override;

    // Loading the track file to deck
    void loadTrackToDeck(File file);

private:


    // Player buttons
    DrawableButton playButton{"PLAY", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton pauseButton{ "PAUSE", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton stopButton{"STOP", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton loopButton{ "LOOP", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton forwardButton{ "FORWARD", DrawableButton::ButtonStyle::ImageOnButtonBackground };
    DrawableButton backwardButton{ "BACKWARD",DrawableButton::ButtonStyle::ImageOnButtonBackground };
    TextButton loadButton{ "Load External Track" };
    TextButton sideButton;


    Slider volSlider; 
	Slider posSlider;

    Slider highPassSlider;
    Label highPassSliderLabel;

    Slider lowPassSlider;
    Label lowPassSliderLabel;

    Slider speedSlider;
    Label speedSliderLabel;

    FileChooser fChooser{"Select a file..."};

    Colour playerColour;
    DJAudioPlayer* player;

	String* side;
    DiscArt discArt;

    MyRotarySliderLookAndFeel myRotarySliderLookAndFeel{side};
    MySliderLookAndFeel mySliderLookAndFeel{side};

    WaveformDisplay waveformDisplay;

    LevelMeter levelMeterL;
    LevelMeter levelMeterR;

    TextEditor trackTitleTxt;
    TextEditor trackDurationTxt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
