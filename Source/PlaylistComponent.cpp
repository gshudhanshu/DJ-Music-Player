/*
  ==============================================================================

    PlaylistComponent.cpp
    Created: 23 Feb 2023 3:03:50pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PlaylistComponent.h"

//==============================================================================
PlaylistComponent::PlaylistComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    tableComponent.getHeader().addColumn("Load deck", 1,  100);
    tableComponent.getHeader().addColumn("Track title", 2, 100 );
    tableComponent.getHeader().addColumn("Artist", 3,  100 );
    tableComponent.getHeader().addColumn("Time", 4,  100);
    tableComponent.getHeader().setStretchToFitActive(true);

    tableComponent.autoSizeAllColumns();
    addAndMakeVisible(tableComponent);

    actions.getHeader().addColumn("Actions", 1, 100, 1, -1, TableHeaderComponent::notSortable );

	actions.getHeader().setStretchToFitActive(true);

    addAndMakeVisible(actions);

}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint (juce::Graphics& g)
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
    g.drawText ("PlaylistComponent", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{

    juce::FlexBox playlistFlex;
    playlistFlex.items.add(juce::FlexItem(actions).withFlex(1));
    playlistFlex.items.add(juce::FlexItem(tableComponent).withFlex(4));

    actions.autoSizeAllColumns();
    tableComponent.autoSizeAllColumns();


    playlistFlex.performLayout(getLocalBounds().toFloat());

    // This method is where you should set the bounds of any child
    // components that your component contains..

}
