/*
  ==============================================================================

    DJAudioPlayer.h
    Created: 13 Mar 2020 4:22:22pm
    Author:  matthew

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"


class DJAudioPlayer : public AudioSource, public ChangeListener

{
  public:

    DJAudioPlayer(AudioFormatManager& _formatManager);
    ~DJAudioPlayer();

    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void changeListenerCallback(juce::ChangeBroadcaster* source) override;

    void loadURL(URL audioURL);

    void setGain(double gain);
    void setSpeed(double ratio);
    void setPosition(double posInSecs);
    void setPositionRelative(double pos);

    void setBass(double bass);
    void setTreble(double treble);

    

    void start();
    void stop();
    void backward();
    void forward();
    void pause();
    void loop();

    Array <float> getDecible();

    /** get the relative position of the playhead */
    double getPositionRelative();
    Array <String> getTrackDetails();

    bool isPlaying();

    void setPlayerColour(Colour colour);
    Colour getPlayerColour();


private:

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

    String trackTitle;
    int trackSeconds;

    Colour playerColor;
    float leftDB;
    float rightDB;

};




