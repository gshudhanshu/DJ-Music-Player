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
PlaylistComponent::PlaylistComponent(DeckGUI* deckGUI1, DeckGUI* deckGUI2)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.


    playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/hard.mp3"));
    playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/hard.mp3"));
    playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/hard.mp3"));
    playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/hard.mp3"));



    tableComponent.getHeader().addColumn("Load A", 1,  50, 50,50);
    tableComponent.getHeader().addColumn("Load B", 2, 50, 50, 50);

    tableComponent.getHeader().addColumn("Track title", 3, 100 );
    tableComponent.getHeader().addColumn("Artist", 4,  100 );
    tableComponent.getHeader().addColumn("Time", 5,  100);
    tableComponent.getHeader().setStretchToFitActive(true);

    tableComponent.setModel(this);

    tableComponent.autoSizeAllColumns();
    addAndMakeVisible(tableComponent);

    actions.getHeader().addColumn("Actions", 1, 100, 1, -1, TableHeaderComponent::notSortable );

	actions.setModel(this);
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

int PlaylistComponent::getNumRows()
{
	return playlistArr.size();
}
void PlaylistComponent::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowIsSelected)
    {
        g.fillAll(Colours::orange);
    } else
    {
        g.fillAll(Colours::darkgrey);
    }
	
} 
void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    if (TableListBoxModel* const tableModel = tableComponent.getModel())
    {
        g.drawText(playlistArr[rowNumber].getFileName(), 0, 0, width, height, Justification::centredLeft);

    }

    if (TableListBoxModel* const tableModel = actions.getModel())
    {
        // g.drawText(playlistArr[rowNumber].getFileName(), 0, 0, width, height, Justification::centredLeft);
    }
}



Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    // Import svg button SVGs
    auto playSvg = Drawable::createFromImageData(BinaryData::play_solid_svg, BinaryData::play_solid_svgSize);

	if(existingComponentToUpdate == nullptr)
	{
        if (columnId == 1) {
            DrawableButton* loadDeck1 = new DrawableButton{ "PLAY", DrawableButton::ButtonStyle::ImageOnButtonBackground };
            loadDeck1->setImages(playSvg.get());
            loadDeck1->addListener(this);
            String id = String(rowNumber);
            loadDeck1->setComponentID(id);
            existingComponentToUpdate = loadDeck1;
        } else if (columnId == 2)
        {
	        DrawableButton* loadDeck2 = new DrawableButton{ "PLAY", DrawableButton::ButtonStyle::ImageOnButtonBackground };
            loadDeck2->setImages(playSvg.get());
            loadDeck2->addListener(this);
            String id = String(rowNumber);
            loadDeck2->setComponentID(id);
			existingComponentToUpdate = loadDeck2;
		}
        
	}
    return existingComponentToUpdate;
}

void PlaylistComponent::buttonClicked(Button* button)
{
    int id = std::stoi(button->getComponentID().toStdString());
    std::cout << "button " << id << std::endl;
    DBG(id);
}