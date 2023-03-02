/*
  ==============================================================================

    DiscArt.cpp
    Created: 2 Mar 2023 12:46:56pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DiscArt.h"

//==============================================================================
DiscArt::DiscArt()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

DiscArt::~DiscArt()
{
}

void DiscArt::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawText ("DiscArt", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void DiscArt::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
