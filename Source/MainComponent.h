/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "Header.h"
#include "PlaylistComponent.h"
#include "MyLookAndFeel.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;


private:
    //==============================================================================
    // Your private member variables go here...

    MyTextButtonLookAndFeel myTextButtonLookAndFeel;
    MyResizableWindowLookAndFeel myResizableWindowLookAndFeel;

    AudioFormatManager formatManager;

    AudioThumbnailCache thumbCache{100};

    Header header;

    DJAudioPlayer player1{formatManager};
    DJAudioPlayer player2{ formatManager };


    String left = "A";
    DeckGUI deckGUI1{&player1, &left, formatManager, thumbCache };

    String right = "B";
    DeckGUI deckGUI2{&player2, &right, formatManager, thumbCache};

    PlaylistComponent playlistComponent{ &deckGUI1, &deckGUI2 };

    MixerAudioSource mixerSource; 
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
