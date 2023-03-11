/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "Utilities.h"


class DJAudioPlayer : public AudioSource, public ChangeListener

{
  public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    // AudioSource methods
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    // ChangeListener methods
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    // Load a new audio file
    void loadURL(URL audioURL);

    // Set the gain of the audio file
    void setGain(double gain);

    // Set the speed of the audio file
    void setSpeed(double ratio);

    // Set the position of the audio file
    void setPosition(double posInSecs);

    // Set the position of the audio file relative to the length of the file
    void setPositionRelative(double pos);

    // Set the bass
    void setBass(double bass);

    // Set the treble
    void setTreble(double treble);
    
    // Start the audio file
    void start();

    // Stop the audio file
    void stop();

    // Backward the audio file by 5 seconds
    void backward();

	// Forward the audio file by 5 seconds
    void forward();

    // Pause the audio file
	void pause();

    // Loop the audio file
    void loop();

    // Get the decibel value array (L, R channel) of the audio file
    Array <float> getDecible();

    // Get the relative position of the playhead
    double getPositionRelative();

    // Get the track details array (Title, Length)
    Array <String> getTrackDetails();

    // Check if the audio file is playing and return true or false
    bool isPlaying();

    // Set player theme colour
    void setPlayerColour(Colour colour);

    // Get player theme colour
    Colour getPlayerColour();

private:

    Utilities utils;

    bool isLooping = false;

    AudioFormatReader* reader;
    AudioFormatManager& formatManager;

    double trackSampleRate;
    int bassCutOffFreq = 300;
    int trebleCutOffFreq = 3000;

    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource; 
    ResamplingAudioSource resampleSource{&transportSource, false, 2};

	IIRFilterAudioSource bassSource{ &resampleSource, false };
    IIRFilterAudioSource trebleSource{ &bassSource, false };
    IIRFilterAudioSource filteredResampleSource{ &trebleSource, false };

    Colour playerColor;
	String trackTitle;
    int trackSeconds;

    float leftDB;
    float rightDB;
};




