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
	PlaylistComponent(
		DeckGUI* _deckGUI1,
		DeckGUI* _deckGUI2);

	~PlaylistComponent() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	int getNumRows() override;
	void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
	void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
	Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

	void buttonClicked(Button* button) override;

	String convertSecTohhmmssFormat(int seconds);


private:

	AudioFormatManager formatManager;

	// Playlist table
	TableListBox tableComponent;
	Array <juce::File> playlistArr;
	Array<juce::File> filteredPlaylistArr;
	Array <int> playlistArrIndex;

	// Actions buttons
	TextButton importTracksBtn{ "Import Tracks" };
	TextButton importPlaylistBtn{ "Import Playlist" };
	TextButton exportPlaylistBtn{ "Export Playlist" };
	TextButton clearPlaylistBtn{ "Clear Playlist" };
	// Actions search bar
	TextEditor searchInput{ "Search" };

	// File Choosers/Exporters
	FileChooser musicTracksChooser{ "Select music tracks"};
	FileChooser exportPlaylist{ "Export Playlist", File(), "*.txt"};
	FileChooser importPlaylist{ "Import Playlist", File(), "*.txt" };


	// Playlist functions
	void importTracksToPlaylist();
	void importExportedPlaylist();
	void exportTracksFromPlaylist();
	void deleteTrackFromPlaylist(int id);
	void clearPlaylist();
	void searchTrackInPlaylist(String textString);

	void autoImportDefaultPlaylist(String path);
	void autoExportDefaultPlaylist(String path);


	DeckGUI* deckGUI1;
	DeckGUI* deckGUI2;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
