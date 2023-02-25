/*
  ==============================================================================

	PlaylistComponent.h
	Created: 23 Feb 2023 3:03:50pm
	Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include "DeckGUI.h"

//==============================================================================
/*
*/
class PlaylistComponent : public juce::Component,
	public TableListBoxModel,
	public Button::Listener
{
public:
	PlaylistComponent(DeckGUI* deckGUI1, DeckGUI* deckGUI2);

	~PlaylistComponent() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	int getNumRows() override;
	void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

	void buttonClicked(Button* button) override;

private:

	// Playlist table
	TableListBox tableComponent;
	Array <juce::File> playlistArr;
	Array<juce::File> filteredPlaylistArr;

	// Actions table
	TableListBox actions;
	// Actions buttons
	TextButton importTracks{ "Import Tracks" };
	TextButton exportTracks{ "Import Tracks" };
	TextButton deleteTrack{ "Import Tracks" };
	TextButton clearPlaylist{ "Import Tracks" };
	// Actions search bar
	TextEditor searchInput{ "Search..." };

	// Playlist functions
	void importTracksToPlaylist();
	void exportTracksFromPlaylist();
	void deleteTrackFromPlaylist(int id);
	void clearPlaylistFromTracks();
	void searchTrackInPlaylist(String textString);

	DeckGUI* deckGUI1;
	DeckGUI* deckGUI2;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
