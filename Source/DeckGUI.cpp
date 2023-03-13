/*
  ==============================================================================

	DeckGUI.cpp
	Created: 13 Mar 2020 6:44:48pm
	Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, String* _side,
	juce::AudioFormatManager& formatManagerToUse,
	juce::AudioThumbnailCache& cacheToUse)
	: player(_player), side(_side),
	waveformDisplay(formatManagerToUse, cacheToUse, playerColour),
	levelMeterL(_player), levelMeterR(_player),
	diskArt(_player)

{
	// Import svg button SVGs
	auto playSvg = Drawable::createFromImageData(BinaryData::play_solid_svg, BinaryData::play_solid_svgSize);
	auto backwardSvg = Drawable::createFromImageData(BinaryData::backward_solid_svg, BinaryData::backward_solid_svgSize);
	auto forwardSvg = Drawable::createFromImageData(BinaryData::forward_solid_svg, BinaryData::forward_solid_svgSize);
	auto pauseSvg = Drawable::createFromImageData(BinaryData::pause_solid_svg, BinaryData::pause_solid_svgSize);
	auto stopSvg = Drawable::createFromImageData(BinaryData::stop_solid_svg, BinaryData::stop_solid_svgSize);
	auto loopSvg = Drawable::createFromImageData(BinaryData::repeat_solid_svg, BinaryData::repeat_solid_svgSize);

	// Setting up the buttons text and images
	playButton.setImages(playSvg.get());
	stopButton.setImages(stopSvg.get());
	pauseButton.setImages(pauseSvg.get());
	backwardButton.setImages(backwardSvg.get());
	forwardButton.setImages(forwardSvg.get());
	loopButton.setClickingTogglesState(true);
	loopButton.setImages(loopSvg.get());

	sideButton.setButtonText(*side);

	// Low pass filter slider
	lowPassSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	lowPassSlider.setRange(0.1, 2.0);
	lowPassSlider.setValue(1.0);
	lowPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
	lowPassSlider.setLookAndFeel(&myRotarySliderLookAndFeel);

	lowPassSliderLabel.setText("Bass", NotificationType::dontSendNotification);
	lowPassSliderLabel.attachToComponent(&lowPassSlider, false);
	lowPassSliderLabel.setJustificationType(Justification::centredBottom);

	// High pass filter slider
	highPassSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	highPassSlider.setRange(0.1, 2.0);
	highPassSlider.setValue(1.0);
	highPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
	highPassSlider.setLookAndFeel(&myRotarySliderLookAndFeel);

	highPassSliderLabel.setText("Treble", NotificationType::dontSendNotification);
	highPassSliderLabel.attachToComponent(&highPassSlider, false);
	highPassSliderLabel.setJustificationType(Justification::centredBottom);

	// Speed slider
	speedSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
	speedSlider.setRange(0.0, 5.0);
	speedSlider.setValue(1.0);
	speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 50, 20);
	speedSlider.setLookAndFeel(&myRotarySliderLookAndFeel);

	speedSliderLabel.setText("Speed", NotificationType::dontSendNotification);
	speedSliderLabel.attachToComponent(&speedSlider, false);
	speedSliderLabel.setJustificationType(Justification::centredBottom);

	// Volume slider
	volSlider.setSliderStyle(juce::Slider::LinearVertical);
	volSlider.setRange(0.0, 1.0);
	volSlider.setValue(1.0);
	volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	volSlider.setLookAndFeel(&mySliderLookAndFeel);

	// Decibel level meters for left and right channels
	levelMeterL.setChannel(0);
	levelMeterR.setChannel(1);

	//posSlider.setRange(0.0, 1.0);

	// Setting track title and duration text boxes
	trackTitleTxt.setText("Track not loaded");
	trackTitleTxt.setJustification(Justification::centred);
	trackDurationTxt.setText("00:00");
	trackDurationTxt.setJustification(Justification::centred);
	trackTitleTxt.setReadOnly(true);
	trackDurationTxt.setReadOnly(true);

	// Making all the elements visible
	addAndMakeVisible(sideButton);
	addAndMakeVisible(diskArt);
	addAndMakeVisible(playButton);
	addAndMakeVisible(stopButton);
	addAndMakeVisible(pauseButton);
	addAndMakeVisible(backwardButton);
	addAndMakeVisible(forwardButton);
	addAndMakeVisible(loopButton);
	addAndMakeVisible(loadButton);

	addAndMakeVisible(levelMeterL);
	addAndMakeVisible(levelMeterR);
	addAndMakeVisible(volSlider);

	addAndMakeVisible(highPassSlider);
	addAndMakeVisible(lowPassSlider);
	addAndMakeVisible(speedSlider);

	addAndMakeVisible(posSlider);

	addAndMakeVisible(waveformDisplay);
	addAndMakeVisible(trackTitleTxt);
	addAndMakeVisible(trackDurationTxt);

	// Adding the listeners
	waveformDisplay.addMouseListener(this, false);

	playButton.addListener(this);
	stopButton.addListener(this);
	pauseButton.addListener(this);
	backwardButton.addListener(this);
	forwardButton.addListener(this);
	loopButton.addListener(this);
	loadButton.addListener(this);

	volSlider.addListener(this);
	highPassSlider.addListener(this);
	lowPassSlider.addListener(this);
	speedSlider.addListener(this);
	posSlider.addListener(this);

	startTimerHz(30);
}

DeckGUI::~DeckGUI()
{
	stopTimer();
}

void DeckGUI::paint(Graphics& g)
{

	// g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

	//g.setColour(Colours::grey);
	//g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	// g.setColour(Colours::white);
	// g.setFont(14.0f);
	//g.drawText("DeckGUI", getLocalBounds(),
		//Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
	// Initializing the flexboxes
	juce::FlexBox mainGUI;
	juce::FlexBox playerButtons;
	juce::FlexBox trackInfo;
	juce::FlexBox diskArtAdjKnobsAndVol;
	juce::FlexBox adjKnobs;
	juce::FlexBox volumeMeterAndVolSlider;
	juce::FlexBox trackTitleDuration;

	playerColour = player->getPlayerColour();
	sideButton.setColour(TextButton::buttonColourId, playerColour);
	sideButton.setColour(TextButton::textColourOffId, findColour(ResizableWindow::backgroundColourId));
	loadButton.setColour(TextButton::buttonColourId, playerColour);
	loadButton.setColour(TextButton::textColourOffId, findColour(ResizableWindow::backgroundColourId));

	// Setting the flexbox properties
	playerButtons.items.add(FlexItem(backwardButton).withFlex(1));
	playerButtons.items.add(FlexItem(playButton).withFlex(1));
	playerButtons.items.add(FlexItem(pauseButton).withFlex(1));
	playerButtons.items.add(FlexItem(forwardButton).withFlex(1));
	playerButtons.items.add(FlexItem(stopButton).withFlex(1));
	playerButtons.items.add(FlexItem(loopButton).withFlex(1));

	volumeMeterAndVolSlider.items.add(FlexItem(levelMeterL).withFlex(1));
	volumeMeterAndVolSlider.items.add(FlexItem(volSlider).withFlex(1));
	volumeMeterAndVolSlider.items.add(FlexItem(levelMeterR).withFlex(1));

	adjKnobs.flexDirection = juce::FlexBox::Direction::column;
	adjKnobs.items.add(FlexItem().withFlex(0.3));
	adjKnobs.items.add(FlexItem(lowPassSlider).withFlex(1));
	adjKnobs.items.add(FlexItem().withFlex(0.3));
	adjKnobs.items.add(FlexItem(highPassSlider).withFlex(1));
	adjKnobs.items.add(FlexItem().withFlex(0.3));
	adjKnobs.items.add(FlexItem(speedSlider).withFlex(1));

	// Left side of the GUI
	if (*side == String("A"))
	{
		diskArtAdjKnobsAndVol.items.add(FlexItem(sideButton).withFlex(0.5));
		diskArtAdjKnobsAndVol.items.add(FlexItem(diskArt).withFlex(4));
		diskArtAdjKnobsAndVol.items.add(FlexItem(adjKnobs).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem(volumeMeterAndVolSlider).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem().withFlex(0.1));
	}
	// Right side of the GUI
	else if (*side == String("B"))
	{
		diskArtAdjKnobsAndVol.items.add(FlexItem().withFlex(0.1));
		diskArtAdjKnobsAndVol.items.add(FlexItem(volumeMeterAndVolSlider).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem(adjKnobs).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem(diskArt).withFlex(4));
		diskArtAdjKnobsAndVol.items.add(FlexItem(sideButton).withFlex(0.5));
	}

	// Track title and duration
	trackInfo.items.add(FlexItem(trackTitleTxt).withFlex(3));
	trackInfo.items.add(FlexItem(trackDurationTxt).withFlex(1));

	// Main GUI
	mainGUI.flexDirection = juce::FlexBox::Direction::column;
	mainGUI.items.add(FlexItem(diskArtAdjKnobsAndVol).withFlex(5));
	mainGUI.items.add(FlexItem(trackInfo).withFlex(0.75));
	mainGUI.items.add(FlexItem(waveformDisplay).withFlex(1));
	mainGUI.items.add(FlexItem(playerButtons).withFlex(0.75));
	mainGUI.items.add(FlexItem(loadButton).withFlex(0.75));

	mainGUI.performLayout(getLocalBounds().toFloat());
	sideButton.setTransform(AffineTransform::rotation(MathConstants<float>::pi * 8 / 4.0f, sideButton.getWidth() / 2.0f, sideButton.getHeight() / 2.0f));
}

// On button click event
void DeckGUI::buttonClicked(Button* button)
{
	if (button == &playButton)
	{
		std::cout << "Play button was clicked " << std::endl;
		player->start();
		diskArt.setRotationSpeed(1);
	}

	if (button == &stopButton)
	{
		std::cout << "Stop button was clicked " << std::endl;
		player->stop();
		diskArt.setRotationSpeed(0);
	}

	if (button == &pauseButton)
	{
		std::cout << "Pause button was clicked " << std::endl;
		player->pause();
		diskArt.setRotationSpeed(0);
	}

	if (button == &backwardButton)
	{
		std::cout << "Backward button was clicked " << std::endl;
		player->backward();
	}

	if (button == &forwardButton)
	{
		std::cout << "Forward button was clicked " << std::endl;
		player->forward();
	}

	// Loop button toggle
	if (button == &loopButton && player->isPlaying())
	{
		if (loopButton.getToggleState())
		{
			loopButton.setColour(TextButton::buttonColourId, player->getPlayerColour());
			loopButton.setColour(TextButton::buttonOnColourId, player->getPlayerColour());
		}
		else
		{
			loopButton.setColour(TextButton::buttonColourId, Colour(0xff1e253a));
			loopButton.setColour(TextButton::buttonOnColourId, Colour(0xff1e253a));
		}

		std::cout << "Stop button was clicked " << std::endl;
		player->loop();
	}
	// if there is no track is playing reset the toggle state to false
	else
	{
		loopButton.setToggleState(false, NotificationType::dontSendNotification);
		loopButton.setColour(TextButton::buttonColourId, Colour(0xff1e253a));
		loopButton.setColour(TextButton::buttonOnColourId, Colour(0xff1e253a));
	}

	if (button == &loadButton)
	{
		auto fileChooserFlags =
			FileBrowserComponent::canSelectFiles;
		fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
		{
			player->loadURL(URL{ chooser.getResult() });
			waveformDisplay.loadURL(URL{ chooser.getResult() });
		});
		diskArt.setRotationSpeed(0);
	}
}

// Slider value change events
void DeckGUI::sliderValueChanged(Slider* slider)
{
	if (slider == &volSlider)
	{
		player->setGain(slider->getValue());
	}
	if (slider == &highPassSlider)
	{
		player->setTreble(slider->getValue());
	}
	if (slider == &lowPassSlider)
	{
		player->setBass(slider->getValue());
	}

	if (slider == &speedSlider)
	{
		player->setSpeed(slider->getValue());
		if (player->isPlaying()) {
			diskArt.setRotationSpeed(slider->getValue());
		}
	}
}

//Mouse down events
void DeckGUI::mouseDown(const MouseEvent& event)
{
	if (event.eventComponent == &waveformDisplay) {
		float pos = static_cast<float>(event.getMouseDownX()) / waveformDisplay.getWidth();
		player->setPositionRelative(pos);
	}
}


bool DeckGUI::isInterestedInFileDrag(const StringArray& files)
{
	std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
	return true;
}

// Load first track after drag and drop of the file in the deck player
void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
	std::cout << "DeckGUI::filesDropped" << std::endl;
	if (files.size() == 1)
	{
		loadTrackToDeck(File{ files[0] });
	}
}

void DeckGUI::loadTrackToDeck(File file)
{
	player->loadURL(URL{ file });
	waveformDisplay.loadURL(URL{ file });
	trackTitleTxt.setText(URL::removeEscapeChars(player->getTrackDetails()[0]));
	trackDurationTxt.setText(player->getTrackDetails()[1]);
	player->start();

	// Start disk rotation
	if (player->isPlaying()) {
		diskArt.setRotationSpeed(speedSlider.getValue());
	}
}


void DeckGUI::timerCallback()
{
	waveformDisplay.setPositionRelative(player->getPositionRelative());
	trackDurationTxt.setText(player->getTrackDetails()[1]);

	if (!player->isPlaying()) {
		diskArt.setRotationSpeed(0);
	}

	// Set decibels to the level meters
	levelMeterL.setValue(player->getDecible()[0]);
	levelMeterR.setValue(player->getDecible()[1]);
}