/*
  ==============================================================================

	WaveformDisplay.cpp
	Created: 14 Mar 2020 3:50:16pm
	Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WaveformDisplay.h"

//==============================================================================
WaveformDisplay::WaveformDisplay(AudioFormatManager& formatManagerToUse,
	AudioThumbnailCache& cacheToUse, Colour& playerColour) :
	audioThumb(1000, formatManagerToUse, cacheToUse),
	fileLoaded(false),
	position(0), playerColour(&playerColour)

{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	audioThumb.addChangeListener(this);
}

WaveformDisplay::~WaveformDisplay()
{
}

void WaveformDisplay::paint(Graphics& g)
{
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(*playerColour);

	if (fileLoaded)
	{
		audioThumb.drawChannel(g,
			getLocalBounds(),
			0,
			audioThumb.getTotalLength(),
			0,
			1.0f
		);

		Path triangleTop, triangleBottom;
		int triangleSize = 7; // Size of the triangle

		// get relative position of x
		double currentPosition = position * getWidth();

		triangleTop.addTriangle(
			currentPosition - triangleSize, 0,
			currentPosition + triangleSize, 0,
			currentPosition, triangleSize
		);

		triangleBottom.addTriangle(
			currentPosition - triangleSize, getHeight(),
			currentPosition + triangleSize, getHeight(),
			currentPosition, getHeight() - triangleSize
		);

		// draw a line at the current play position
		g.setColour(Colours::red);
		g.fillRect(currentPosition, 0, 2, getHeight());
		//g.drawRect(position * getWidth(), 0, 5, getHeight(), 1);
		g.fillPath(triangleTop);
		g.fillPath(triangleBottom);
	}
	else
	{
		g.setFont(20.0f);
		g.drawText("File not loaded...", getLocalBounds(),
			Justification::centred, true);   // draw some placeholder text
	}
}

void WaveformDisplay::resized()
{
	// This method is where you should set the bounds of any child
	// components that your component contains..
}

void WaveformDisplay::loadURL(URL audioURL)
{
	audioThumb.clear();
	fileLoaded = audioThumb.setSource(new URLInputSource(audioURL));
	if (fileLoaded)
	{
		std::cout << "wfd: loaded! " << std::endl;
		repaint();
	}
	else {
		std::cout << "wfd: not loaded! " << std::endl;
	}
}

void WaveformDisplay::changeListenerCallback(ChangeBroadcaster* source)
{
	std::cout << "wfd: change received! " << std::endl;

	repaint();
}

void WaveformDisplay::setPositionRelative(double pos)
{
	if (pos != position && pos >= 0)
	{
		position = pos;
		repaint();
	}
}

float WaveformDisplay::getMousePosition()
{
	return getMouseXYRelative().getX() / getWidth();
}