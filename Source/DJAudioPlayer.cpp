/*
==============================================================================

DJAudioPlayer.cpp
Created: 13 Mar 2020 4:22:22pm
Author:  matthew

==============================================================================
*/

#include "DJAudioPlayer.h"

DJAudioPlayer::DJAudioPlayer(AudioFormatManager& _formatManager)
	: formatManager(_formatManager)
{
}

DJAudioPlayer::~DJAudioPlayer()
{
	transportSource.setSource(nullptr);
}

void DJAudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	trackSampleRate = sampleRate;
	transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

	resampleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

	bassSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
	trebleSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

	bassSource.setCoefficients(juce::IIRCoefficients::makeLowShelf(sampleRate, bassCutOffFreq, 1, 1));
	trebleSource.setCoefficients(juce::IIRCoefficients::makeHighShelf(sampleRate, trebleCutOffFreq, 1, 1));
	filteredResampleSource.setCoefficients(juce::IIRCoefficients::makeAllPass(sampleRate, 200));
	
}
void DJAudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	filteredResampleSource.getNextAudioBlock(bufferToFill);

	if (reader != nullptr)
	{
		AudioBuffer<float> buffer(2, bufferToFill.numSamples); // create new buffer for channel data

		buffer.copyFrom(0, 0, bufferToFill.buffer->getReadPointer(0), bufferToFill.numSamples);
		buffer.copyFrom(1, 0, bufferToFill.buffer->getReadPointer(1), bufferToFill.numSamples);

		//AudioBuffer<float> leftChannel(1, bufferToFill.numSamples); // create new buffer for left channel data
		//AudioBuffer<float> rightChannel(1, bufferToFill.numSamples); // create new buffer for left channel data

		//leftChannel.copyFrom(0, 0, bufferToFill.buffer->getReadPointer(0), bufferToFill.numSamples);
		// copy left channel data from bufferToFill to leftChannel

		//rightChannel.copyFrom(0, 0, bufferToFill.buffer->getReadPointer(1), bufferToFill.numSamples);
		// copy right channel data from bufferToFill to rightChannel

		//// Calculate RMS values for left and right channels
		//float leftRMS = buffer.getRMSLevel(0, 0, bufferToFill.numSamples);
		//float rightRMS = buffer.getRMSLevel(0, 0, bufferToFill.numSamples);

		// Calculate RMS values for left and right channels
		//float leftRMS = buffer.getRMSLevel(0, 0, bufferToFill.numSamples);
		float leftRMS = buffer.getRMSLevel(0, 0, bufferToFill.numSamples);
		//float leftRMS = buffer.getRMSLevel(0, 0, bufferToFill.numSamples);
		float rightRMS = buffer.getRMSLevel(1, 0, bufferToFill.numSamples);

		// Decible Adjestment
		float referenceValue = 0.35f;

		leftDB = Decibels::gainToDecibels(leftRMS* referenceValue);
		rightDB = Decibels::gainToDecibels(rightRMS * referenceValue);

		//leftDB = 20.0f * std::log10(leftRMS / referenceValue);
		//rightDB = 20.0f * std::log10(rightRMS / referenceValue);
	}

}
void DJAudioPlayer::releaseResources()
{
	transportSource.releaseResources();
	resampleSource.releaseResources();
	bassSource.releaseResources();
	trebleSource.releaseResources();
	filteredResampleSource.releaseResources();
}

void DJAudioPlayer::loadURL(URL audioURL)
{
	reader = formatManager.createReaderFor(audioURL.createInputStream(false));
	if (reader != nullptr) // good file!
	{
		std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader,
			true));
		transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
		readerSource.reset(newSource.release());

		trackTitle = audioURL.getFileName();
		trackSeconds = transportSource.getLengthInSeconds();
	}
}
void DJAudioPlayer::setGain(double gain)
{
	if (gain < 0 || gain > 1.0)
	{
		std::cout << "DJAudioPlayer::setGain gain should be between 0 and 1" << std::endl;
	}
	else {
		transportSource.setGain(gain);
	}
}

void DJAudioPlayer::setBass(double bass)
{
	if (bass < 0 || bass > 2)
	{
		DBG("DJAudioPlayer::setBass ratio should be between 0 and 2");
	}
	else
	{
		bassSource.setCoefficients(juce::IIRCoefficients::makeLowShelf(trackSampleRate, bassCutOffFreq, 1, bass));
	}
}

void DJAudioPlayer::setTreble(double treble)
{
	if (treble < 0 || treble > 2)
	{
		DBG("DJAudioPlayer::setTreble ratio should be between 0 and 2");
	}
	else
	{
		trebleSource.setCoefficients(juce::IIRCoefficients::makeHighShelf(trackSampleRate, trebleCutOffFreq, 1, treble));
	}
}

void DJAudioPlayer::setSpeed(double ratio)
{
	if (ratio < 0 || ratio > 100.0)
	{
		std::cout << "DJAudioPlayer::setSpeed ratio should be between 0 and 100" << std::endl;
	}
	else {
		resampleSource.setResamplingRatio(ratio);
	}
}
void DJAudioPlayer::setPosition(double posInSecs)
{
	transportSource.setPosition(posInSecs);
}

void DJAudioPlayer::setPositionRelative(double pos)
{
	if (pos < 0 || pos > 1.0)
	{
		std::cout << "DJAudioPlayer::setPositionRelative pos should be between 0 and 1" << std::endl;
	}
	else {
		double posInSecs = transportSource.getLengthInSeconds() * pos;
		setPosition(posInSecs);
	}
}

void DJAudioPlayer::start()
{
	transportSource.start();
}
void DJAudioPlayer::stop()
{
	transportSource.stop();
	transportSource.setPosition(0);
}

void DJAudioPlayer::backward()
{
	auto currentPos = transportSource.getCurrentPosition();
	if(currentPos < 5)
	{
		transportSource.setPosition(0);
	} else
	{
	transportSource.setPosition(currentPos - 5); // 5 seconds back from current position
	}
}
void DJAudioPlayer::forward()
{
	auto currentPos = transportSource.getCurrentPosition();
	auto totalSec = transportSource.getLengthInSeconds();
	if (totalSec - currentPos < 5)
	{
		transportSource.setPosition(totalSec);
	}
	else
	{
		transportSource.setPosition(currentPos + 5); // 5 seconds forward from current position
	}
}
void DJAudioPlayer::pause()
{
	transportSource.stop();
}
void DJAudioPlayer::loop()
{
	if (transportSource.isLooping())
	{
		
		readerSource->setLooping(false);
	}
	else
	{
		readerSource->setLooping(true);
	}
}




double DJAudioPlayer::getPositionRelative()
{
	return transportSource.getCurrentPosition() / transportSource.getLengthInSeconds();
}

Array <String> DJAudioPlayer::getTrackDetails()
{
	String hr0, min0, sec0;
	int hr = (trackSeconds / 3600);
	int min = (trackSeconds / 60) % 60;
	int sec = (trackSeconds % 60);
	if (hr < 10) {
		hr0 = "0";
	}
	if (min < 10) {
		min0 = "0";
	}
	if (sec < 10) {
		sec0 = "0";
	}

	String time = hr0 + String(hr) + ":" + min0 + String(min) + ":" + sec0 + String(sec);
	return { trackTitle, time };
}

Array <float> DJAudioPlayer::getDecible()
{
	return { leftDB, rightDB };
}

bool DJAudioPlayer::isPlaying()
{
		return transportSource.isPlaying();
}



void DJAudioPlayer::setPlayerColour(Colour colour)
{
	playerColor = colour;
}

Colour DJAudioPlayer::getPlayerColour()
{
	return playerColor;
}