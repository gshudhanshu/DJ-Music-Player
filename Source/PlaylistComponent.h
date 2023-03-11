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
#include "Utilities.h"


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

	// Get number of rows of the table
	int getNumRows() override;

	// Paint the row background
	void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;

	// Paint the cell content
	void paintCell(Graphics&, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;

	// Function to refresh the custom components in the table
	Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

	// Button clicked events handler
	void buttonClicked(Button* button) override;

private:

	Utilities utils;

	AudioFormatManager formatManager;

	std::unique_ptr <Drawable> playSvg, deleteSvg;

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

	// Import tracks to playlist using file chooser
	void importTracksToPlaylist();

	// Import playlist using file chooser (txt file)
	void importExportedPlaylist();

	// Export playlist using file chooser (txt file)
	void exportTracksFromPlaylist();

	// Delete track from playlist using row number
	void deleteTrackFromPlaylist(int id);

	// Clear playlist
	void clearPlaylist();

	// Search track in playlist using text string
	void searchTrackInPlaylist(String textString);

	// Import default playlist from default path
	void autoImportDefaultPlaylist(String path);

	// Export playlist to default path
	void autoExportDefaultPlaylist(String path);

	// Decks GUI pointers
	DeckGUI* deckGUI1;
	DeckGUI* deckGUI2;

	// Active track button pointers
	Component* activeTrack1 = nullptr;
	Component* activeTrack2 = nullptr;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlaylistComponent)
};
