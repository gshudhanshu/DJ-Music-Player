/*
  ==============================================================================

    LevelMeter.cpp
    Created: 3 Mar 2023 6:24:19pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "LevelMeter.h"

//==============================================================================
LevelMeter::LevelMeter(DJAudioPlayer* _player) : player(_player)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    // Set up default values
    decibles = -30.0f;
    targetValue = -60.0f;
    maxBarHeight = 200.0f;
    barWidth = 50.0f;

    barColour = player->getPlayerColour();

    startTimerHz(60);
}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint (juce::Graphics& g)
{

	// Draw background
    g.setColour(juce::Colours::black);
    g.fillRect(getLocalBounds());

    // Draw bar graph
    float barHeight = juce::jmap(decibles, -60.0f, 0.0f, 0.0f, maxBarHeight);
    if(barHeight < 0.0f) barHeight = 0.0f;
    float x = getWidth() / 2 - barWidth / 2;
    float y = getHeight() - barHeight;
	g.setColour(barColour);
    g.fillRect(x, y, barWidth, barHeight);

}

void LevelMeter::setValue(float newValue)
{
    targetValue = newValue;
}

void LevelMeter::setChannel(int channel)
{
    channel = channel;
}

void LevelMeter::updateValue()
{
    float smoothingFactor = 0.5f;
    //decibles += smoothingFactor * (targetValue - decibles);
    decibles += smoothingFactor * (targetValue - decibles);
}

void LevelMeter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void LevelMeter::timerCallback()
{
    repaint();
    //setValue(player->getDecible()[channel]);
    if(barColour.getBrightness() == 0)
    {
		barColour = player->getPlayerColour();
    }
    updateValue();
}