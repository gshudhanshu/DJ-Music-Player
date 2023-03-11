/*
  ==============================================================================

	This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	// Set player theme colors
	player1.setPlayerColour(Colour(252, 183, 67));
	player2.setPlayerColour(Colour(74, 244, 210));

	// Setting the size of the window
	setSize(1000, 600);

	//LookAndFeel::setDefaultLookAndFeel(&myTextButtonLookAndFeel);
	LookAndFeel::setDefaultLookAndFeel(&myResizableWindowLookAndFeel);

	// Some platforms require permissions to open input channels so request that here
	if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
		&& !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
	{
		RuntimePermissions::request(RuntimePermissions::recordAudio,
			[&](bool granted) { if (granted)  setAudioChannels(2, 2); });
	}
	else
	{
		// Specify the number of input and output channels that we want to open
		setAudioChannels(0, 2);
	}

	addAndMakeVisible(header);
	addAndMakeVisible(playlistComponent);

	addAndMakeVisible(deckGUI1);
	addAndMakeVisible(deckGUI2);

	formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{
	// This shuts down the audio device and clears the audio source.
	shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
	player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
	player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

	mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

	mixerSource.addInputSource(&player1, false);
	mixerSource.addInputSource(&player2, false);

}
void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
	mixerSource.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
	// This will be called when the audio device stops, or when it is being
	// restarted due to a setting change.

	// For more details, see the help for AudioProcessor::releaseResources()
	player1.releaseResources();
	player2.releaseResources();
	mixerSource.releaseResources();
}

//==============================================================================
void MainComponent::paint(Graphics& g)
{
	// (Our component is opaque, so we must completely fill the background with a solid colour)
	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
	// Initialize the flexbox
	juce::FlexBox mainFlexBox;
	juce::FlexBox decks;

	mainFlexBox.flexDirection = juce::FlexBox::Direction::column;
	mainFlexBox.items.add(juce::FlexItem(header).withFlex(0.5));

	decks.flexDirection = juce::FlexBox::Direction::row;
	decks.items.add(juce::FlexItem(deckGUI1).withFlex(1));
	decks.items.add(juce::FlexItem(deckGUI2).withFlex(1));

	mainFlexBox.items.add(juce::FlexItem(decks).withFlex(4));
	mainFlexBox.items.add(juce::FlexItem(playlistComponent).withFlex(2));

	mainFlexBox.performLayout(getLocalBounds().toFloat());
}

