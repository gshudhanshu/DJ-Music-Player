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
PlaylistComponent::PlaylistComponent(
	DeckGUI* _deckGUI1,
	DeckGUI* _deckGUI2): deckGUI1(_deckGUI1), deckGUI2(_deckGUI2)
{
	// In your constructor, you should add any child components, and
	// initialise any special settings that your component needs.

	playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/hard.mp3"));
	playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/hard.mp3"));
	playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/hard.mp3"));
	playlistArr.add(File("G:/UoL/Object-Oriented Programming/Final project/OtoDecks/tracks/Rihanna_Lift_Me_Up_From_Black_Panther_Wakanda_.mp3"));

	tableComponent.getHeader().addColumn("Load A", 1, 50, 50, 50);
	tableComponent.getHeader().addColumn("Load B", 2, 50, 50, 50);

	tableComponent.getHeader().addColumn("Track title", 3, 100);
	tableComponent.getHeader().addColumn("Format", 4, 100, 70, 100);
	tableComponent.getHeader().addColumn("Time", 5, 100, 70, 100);
	tableComponent.getHeader().addColumn("Delete", 6, 50, 50, 50);
	tableComponent.getHeader().setStretchToFitActive(true);

	tableComponent.setModel(this);

	tableComponent.autoSizeAllColumns();
	addAndMakeVisible(tableComponent);

	searchInput.setTextToShowWhenEmpty("Search...", juce::Colours::grey);
	addAndMakeVisible(searchInput);
	addAndMakeVisible(importTracksBtn);
	addAndMakeVisible(importPlaylistBtn);
	addAndMakeVisible(exportPlaylistBtn);
	addAndMakeVisible(clearPlaylistBtn);

	importTracksBtn.addListener(this);
	importPlaylistBtn.addListener(this);
	exportPlaylistBtn.addListener(this);
	clearPlaylistBtn.addListener(this);

}

PlaylistComponent::~PlaylistComponent()
{
}

void PlaylistComponent::paint(juce::Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(juce::Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(juce::Colours::white);
	g.setFont(14.0f);
	g.drawText("Actions", getLocalBounds(),
		juce::Justification::topLeft, true);   // draw some placeholder text
}

void PlaylistComponent::resized()
{
	juce::FlexBox playlistFlex;
	juce::FlexBox actions;

	actions.flexDirection = juce::FlexBox::Direction::column;
	actions.items.add(juce::FlexItem(searchInput).withFlex(1).withMaxHeight(30));
	actions.items.add(juce::FlexItem(importTracksBtn).withFlex(1).withMaxHeight(30));
	actions.items.add(juce::FlexItem(importPlaylistBtn).withFlex(1).withMaxHeight(30));
	actions.items.add(juce::FlexItem(exportPlaylistBtn).withFlex(1).withMaxHeight(30));
	actions.items.add(juce::FlexItem(clearPlaylistBtn).withFlex(1).withMaxHeight(30));

	playlistFlex.items.add(juce::FlexItem(actions).withFlex(1));
	playlistFlex.items.add(juce::FlexItem(tableComponent).withFlex(4));

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
	if (rowIsSelected)
	{
		g.fillAll(Colours::orange);
	}
	else
	{
		g.fillAll(Colours::darkgrey);
	}
}
void PlaylistComponent::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
	if (columnId == 3)
	{
		g.drawText(playlistArr[rowNumber].getFileName(), 0, 0, width, height, Justification::centredLeft);
	}
	if (columnId == 4 || columnId == 5)
	{
		AudioFormatManager formatManager;
		formatManager.registerBasicFormats();
		ScopedPointer<AudioFormatReader> reader = formatManager.createReaderFor(playlistArr[rowNumber]);

		// if (reader) {
		//        for (String key : reader->metadataValues.getAllKeys()) {
		//        DBG("Key: " + key + " value: " + reader->metadataValues.getValue(key, "unknown"));
		//        // DBG("length "+ reader->metadataValues.getAllKeys().size());
		//        }
		//
		//    }

		if (columnId == 4 && reader)
		{
			//Juce is not able to read the metadata of the mp3 file so I am using 'file format' instead of 'artist'.
			g.drawText(reader->getFormatName(), 0, 0, width, height, Justification::centredLeft);
		}
		if (columnId == 5 && reader)
		{
			int seconds = reader->lengthInSamples / reader->sampleRate;
			String time = convertSecTohhmmssFormat(seconds);
			g.drawText(time, 0, 0, width, height, Justification::centredLeft);
		}

		// g.drawText(reader->metadataValues.getValue("artist", ""), 0, 0, width, height, Justification::centredLeft);
	}
	// else if(columnId == 5)
	// {
	//     g.drawText(reader->metadataValues.getValue("duration", ""), 0, 0, width, height, Justification::centredLeft);
	// }
	//
}

Component* PlaylistComponent::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
	// Import svg button SVGs
	auto playSvg = Drawable::createFromImageData(BinaryData::play_solid_svg, BinaryData::play_solid_svgSize);
	auto deleteSvg = Drawable::createFromImageData(BinaryData::trash_solid_svg, BinaryData::trash_solid_svgSize);
	//existingComponentToUpdate == nullptr;
	if (existingComponentToUpdate == nullptr)
	{
		if (columnId == 1) {
			DrawableButton* loadDeck1Btn = new DrawableButton{ "LOAD_DECK_1", DrawableButton::ButtonStyle::ImageOnButtonBackground };
			loadDeck1Btn->setImages(playSvg.get());
			loadDeck1Btn->addListener(this);
			String id = String(rowNumber);
			loadDeck1Btn->setComponentID(id);
			existingComponentToUpdate = loadDeck1Btn;
		}
		else if (columnId == 2)
		{
			DrawableButton* loadDeck2Btn = new DrawableButton{ "LOAD_DECK_2", DrawableButton::ButtonStyle::ImageOnButtonBackground };
			loadDeck2Btn->setImages(playSvg.get());
			loadDeck2Btn->addListener(this);
			String id = String(rowNumber);
			loadDeck2Btn->setComponentID(id);
			existingComponentToUpdate = loadDeck2Btn;
		}
		else if (columnId == 6)
		{
			DrawableButton* deleteTrackBtn = new DrawableButton{ "DELETE_TRACK", DrawableButton::ButtonStyle::ImageOnButtonBackground };
			deleteTrackBtn->setImages(deleteSvg.get());
			deleteTrackBtn->addListener(this);
			String id = String(rowNumber);
			deleteTrackBtn->setComponentID(id);
			existingComponentToUpdate = deleteTrackBtn;
		}
	} else
	{
		existingComponentToUpdate->setComponentID(String(rowNumber));
	}
	return existingComponentToUpdate;
}

void PlaylistComponent::deleteTrackFromPlaylist(int id)
{
	//Reference https://forum.juce.com/t/displaying-okcancel-window/47646
	const auto callback = juce::ModalCallbackFunction::create([this, id](int result) {
		if (result == 0)
		{
			return;
		}// result == 0 means you click Cancel
	if (result == 1)
	{
		playlistArr.remove(id);
		tableComponent.updateContent();
	}// result == 1 means you click OK
		});

	AlertWindow::showOkCancelBox(MessageBoxIconType::QuestionIcon, "Delete Track", "Are you sure you want to delete this track?", "Yes", "No", {},
		callback);
}

void PlaylistComponent::importTracksToPlaylist()
{
	auto flags = FileBrowserComponent::canSelectMultipleItems;
	musicTracksChooser.launchAsync(flags, [this](const FileChooser& chooser)
		{
			auto file = chooser.getResults();
	playlistArr.addArray(file);
	tableComponent.updateContent();
		}
	);
}

void PlaylistComponent::exportTracksFromPlaylist()
{
	auto fileToSave = File::createTempFile("export_playlist.txt");

	for (auto file : playlistArr) {
		fileToSave.appendText(file.getFullPathName() + "\n");
	}

	auto flags = FileBrowserComponent::saveMode;
	exportPlaylist.launchAsync(flags, [this, fileToSave](const FileChooser& chooser)
		{
			auto result = chooser.getURLResult();
	auto name = result.isEmpty() ? String()
		: (result.isLocalFile() ? result.getLocalFile().getFullPathName()
			: result.toString(true));
	if (!result.isEmpty())
	{
		std::unique_ptr<InputStream>  wi(fileToSave.createInputStream());
		std::unique_ptr<OutputStream> wo(result.createOutputStream());
		if (wi.get() != nullptr && wo.get() != nullptr)
		{
			auto numWritten = wo->writeFromInputStream(*wi, -1);
			jassertquiet(numWritten > 0);
			wo->flush();
		}
	}
		}
	);
}

void PlaylistComponent::importExportedPlaylist()
{
	auto flags = FileBrowserComponent::canSelectMultipleItems;
	importPlaylist.launchAsync(flags, [this](const FileChooser& chooser)
		{
			auto result = chooser.getURLResult();
	auto name = result.isEmpty() ? String()
		: (result.isLocalFile() ? result.getLocalFile().getFullPathName()
			: result.toString(true));
	if (!result.isEmpty())
	{
		File file(result.getLocalFile().getFullPathName());

		if (!file.existsAsFile())
			return;  // file doesn't exist

		juce::FileInputStream inputStream(file); // [2]

		if (!inputStream.openedOk())
			return;  // failed to open

		while (!inputStream.isExhausted()) // [3]
		{
			auto line = inputStream.readNextLine();
			playlistArr.add(File(line));
		}
		tableComponent.updateContent();
	}
		}
	);
}

void PlaylistComponent::clearPlaylist()
{
	const auto callback = juce::ModalCallbackFunction::create([this](int result) {
		if (result == 0)
		{
			return;
		}// result == 0 means you click Cancel
	if (result == 1)
	{
		playlistArr.clear();
			tableComponent.updateContent();
	}// result == 1 means you click OK
		});

	AlertWindow::showOkCancelBox(MessageBoxIconType::QuestionIcon, "Clear playlist", "Are you sure you want to clear playlist?", "Yes", "No", {},
		callback);
}

void PlaylistComponent::buttonClicked(Button* button)
{
	int id;
	if (button->getComponentID() != "")
	{
		id = std::stoi(button->getComponentID().toStdString());
	}


	// Delete track from playlist
	if (button->getButtonText() == "DELETE_TRACK")
	{
		deleteTrackFromPlaylist(id);
	}

	else if(button->getButtonText() == "LOAD_DECK_1")
	{
		DBG("LOAD_DECK_1");
		deckGUI1->loadTrackToDeck(playlistArr[id]);
	}

	else if (button->getButtonText() == "LOAD_DECK_2")
	{
		DBG("LOAD_DECK_2");
		deckGUI2->loadTrackToDeck(playlistArr[id]);
	}

	else if (button == &importTracksBtn)
	{
		importTracksToPlaylist();
	}

	else if (button == &importPlaylistBtn)
	{
		importExportedPlaylist();
	}

	else if (button == &exportPlaylistBtn)
	{
		exportTracksFromPlaylist();
	}

	else if (button == &clearPlaylistBtn)
	{
		clearPlaylist();
	}


}

String PlaylistComponent::convertSecTohhmmssFormat(int seconds)
{
	int hr = (seconds / 3600);
	int min = (seconds / 60) % 60;
	int sec = (seconds % 60);
	String time = String(hr) + ":" + String(min) + ":" + String(sec);
	return time;
}