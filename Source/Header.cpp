/*
  ==============================================================================

    Header.cpp
    Created: 20 Feb 2023 6:16:28am
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "Header.h"

//==============================================================================
Header::Header()
{

}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background
    //g.fillAll (Colour(0xff242d47));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 0);   // draw an outline around the component

    g.setColour(juce::Colours::white);
    g.drawLine(0, getHeight(), getWidth(), getHeight(), 1);

    g.setColour (juce::Colours::white);
    g.setFont(Font( 25.0f, Font::bold));

    // Application name
	g.drawText ("EZEE Player", -10, 0, getWidth() / 2, getHeight(),
                juce::Justification::right, true); 
    // Application tagline
	g.setFont(Font(14.0f, Font::plain));
    g.drawText("Simple DJ app", (getWidth() / 2)+10, 0, getWidth() / 2, getHeight(),
        juce::Justification::left, true);  
}

void Header::resized()
{
}
