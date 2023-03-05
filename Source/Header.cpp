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
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

Header::~Header()
{
}

void Header::paint (juce::Graphics& g)
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
    g.setFont(Font( 25.0f, Font::bold));
    g.drawText ("DJ EZEE", -10, 0, getWidth() / 2, getHeight(),
                juce::Justification::right, true); 
    g.setFont(Font(14.0f, Font::plain));
    g.drawText("Simple DJ app", (getWidth() / 2)+10, 0, getWidth() / 2, getHeight(),
        juce::Justification::left, true);  
}

void Header::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
}
