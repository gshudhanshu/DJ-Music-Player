/*
  ==============================================================================

	DeckGUI.cpp
	Created: 13 Mar 2020 6:44:48pm
	Author:  matthew

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeckGUI.h"

//==============================================================================
DeckGUI::DeckGUI(DJAudioPlayer* _player, String* _side,
	juce::AudioFormatManager& formatManagerToUse,
	juce::AudioThumbnailCache& cacheToUse)
	: player(_player), side(_side), waveformDisplay(formatManagerToUse, cacheToUse),
      levelMeterL(_player), levelMeterR(_player),
      discArt(_player)

{


	// Import svg button SVGs
	auto playSvg = Drawable::createFromImageData(BinaryData::play_solid_svg, BinaryData::play_solid_svgSize);
	auto backwardSvg = Drawable::createFromImageData(BinaryData::backward_solid_svg, BinaryData::backward_solid_svgSize);
	auto forwardSvg = Drawable::createFromImageData(BinaryData::forward_solid_svg, BinaryData::forward_solid_svgSize);
	auto pauseSvg = Drawable::createFromImageData(BinaryData::pause_solid_svg, BinaryData::pause_solid_svgSize);
	auto stopSvg = Drawable::createFromImageData(BinaryData::stop_solid_svg, BinaryData::stop_solid_svgSize);
	auto loopSvg = Drawable::createFromImageData(BinaryData::repeat_solid_svg, BinaryData::repeat_solid_svgSize);

	sideButton.setButtonText(*side);


	playButton.setImages(playSvg.get());
	stopButton.setImages(stopSvg.get());
	pauseButton.setImages(pauseSvg.get());
	backwardButton.setImages(backwardSvg.get());
	forwardButton.setImages(forwardSvg.get());
	loopButton.setImages(loopSvg.get());

	highPassSlider.setSliderStyle(juce::Slider::Rotary);
	highPassSlider.setRange(0.1, 2.0);
	highPassSlider.setValue(1.0);
	highPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	highPassSlider.setLookAndFeel(&myRotarySliderLookAndFeel);


	lowPassSlider.setSliderStyle(juce::Slider::Rotary);
	lowPassSlider.setRange(0.1, 2.0);
	lowPassSlider.setValue(1.0);
	lowPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	lowPassSlider.setLookAndFeel(&myRotarySliderLookAndFeel);


	speedSlider.setSliderStyle(juce::Slider::Rotary);
	speedSlider.setRange(0.0, 5.0);
	speedSlider.setValue(1.0);
	speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	speedSlider.setLookAndFeel(&myRotarySliderLookAndFeel);


	volSlider.setSliderStyle(juce::Slider::LinearVertical);
	volSlider.setRange(0.0, 1.0);
	volSlider.setValue(1.0);
	volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);
	volSlider.setLookAndFeel(&mySliderLookAndFeel);


	levelMeterL.setChannel(0);
	levelMeterR.setChannel(1);

	posSlider.setRange(0.0, 1.0);

	trackTitleTxt.setText("Track not loaded");
	trackDurationTxt.setText("00:00");
	trackTitleTxt.isReadOnly();
	trackDurationTxt.isReadOnly();

	addAndMakeVisible(sideButton);
	addAndMakeVisible(discArt);
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

	//startTimer(500);
	startTimerHz(30);
}

DeckGUI::~DeckGUI()
{
	stopTimer();
}

void DeckGUI::paint(Graphics& g)
{
	/* This demo code just fills the component's background and
	   draws some placeholder text to get you started.

	   You should replace everything in this method with your own
	   drawing code..
	*/

	g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));   // clear the background

	g.setColour(Colours::grey);
	g.drawRect(getLocalBounds(), 1);   // draw an outline around the component

	g.setColour(Colours::white);
	g.setFont(14.0f);
	//g.drawText("DeckGUI", getLocalBounds(),
		//Justification::centred, true);   // draw some placeholder text
}

void DeckGUI::resized()
{
	juce::FlexBox mainGUI;
	juce::FlexBox playerButtons;
	juce::FlexBox trackInfo;
	juce::FlexBox diskArtAdjKnobsAndVol;
	juce::FlexBox adjKnobs;
	juce::FlexBox volumeMeterAndVolSlider;
	juce::FlexBox trackTitleDuration;

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
	adjKnobs.items.add(FlexItem(lowPassSlider).withFlex(1));
	adjKnobs.items.add(FlexItem(highPassSlider).withFlex(1));
	adjKnobs.items.add(FlexItem(speedSlider).withFlex(1));

	if(*side == String("A"))
	{
		diskArtAdjKnobsAndVol.items.add(FlexItem(sideButton).withFlex(0.5));
		diskArtAdjKnobsAndVol.items.add(FlexItem(discArt).withFlex(4));
		diskArtAdjKnobsAndVol.items.add(FlexItem(adjKnobs).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem(volumeMeterAndVolSlider).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem().withFlex(0.25));
	} else if(*side == String("B"))
	{
		diskArtAdjKnobsAndVol.items.add(FlexItem().withFlex(0.25));
		diskArtAdjKnobsAndVol.items.add(FlexItem(volumeMeterAndVolSlider).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem(adjKnobs).withFlex(1));
		diskArtAdjKnobsAndVol.items.add(FlexItem(discArt).withFlex(4));
		diskArtAdjKnobsAndVol.items.add(FlexItem(sideButton).withFlex(0.5));
	}

	trackInfo.items.add(FlexItem(trackTitleTxt).withFlex(3));
	trackInfo.items.add(FlexItem(trackDurationTxt).withFlex(1));

	mainGUI.flexDirection = juce::FlexBox::Direction::column;
	mainGUI.items.add(FlexItem(diskArtAdjKnobsAndVol).withFlex(5));
	mainGUI.items.add(FlexItem(trackInfo).withFlex(1));
	mainGUI.items.add(FlexItem(waveformDisplay).withFlex(1));
	mainGUI.items.add(FlexItem(playerButtons).withFlex(1));
	mainGUI.items.add(FlexItem(loadButton).withFlex(1));

	mainGUI.performLayout(getLocalBounds().toFloat());
	sideButton.setTransform(AffineTransform::rotation(MathConstants<float>::pi*8 / 4.0f, sideButton.getWidth() / 2.0f,  sideButton.getHeight() / 2.0f));

	//double rowH = getHeight() / 8;
	//double rowW = getWidth() / 6;
	//backwardButton.setBounds(rowW*0, 0, rowW, rowH);
	//playButton.setBounds(rowW*1, 0, rowW, rowH);
	//pauseButton.setBounds(rowW*2, 0, rowW, rowH);
	//forwardButton.setBounds( rowW*3, 0, rowW, rowH);
	//stopButton.setBounds(rowW*4, 0, rowW, rowH);
	//loopButton.setBounds( rowW*5, 0, rowW, rowH);
	//volSlider.setBounds(0, rowH * 2, getWidth(), rowH);
	//speedSlider.setBounds(0, rowH * 3, getWidth(), rowH);
	//posSlider.setBounds(0, rowH * 4, getWidth(), rowH);
	//waveformDisplay.setBounds(0, rowH * 5, getWidth(), rowH * 2);
	//loadButton.setBounds(0, rowH * 7, getWidth(), rowH);
}

void DeckGUI::buttonClicked(Button* button)
{
	if (button == &playButton)
	{
		std::cout << "Play button was clicked " << std::endl;
		player->start();
		discArt.setRotationSpeed(1);
	}
	if (button == &stopButton)
	{
		std::cout << "Stop button was clicked " << std::endl;
		player->stop();
		discArt.setRotationSpeed(0);
	}

	if (button == &pauseButton)
	{
		std::cout << "Stop button was clicked " << std::endl;
		player->pause();
		discArt.setRotationSpeed(0);
	}	if (button == &backwardButton)
	{
		std::cout << "Stop button was clicked " << std::endl;
		player->backward();
	}	if (button == &forwardButton)
	{
		std::cout << "Stop button was clicked " << std::endl;
		player->forward();
	}	if (button == &loopButton)
	{
		std::cout << "Stop button was clicked " << std::endl;
		player->loop();
	}
	if (button == &loadButton)
	{
		auto fileChooserFlags =
			FileBrowserComponent::canSelectFiles;
		fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
			{
				player->loadURL(URL{ chooser.getResult() });
		// and now the waveformDisplay as well
		waveformDisplay.loadURL(URL{ chooser.getResult() });
			});
		discArt.setRotationSpeed(0);
	}
}

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
		if(player->isPlaying()){
			discArt.setRotationSpeed(slider->getValue());
		}
	}

}

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

void DeckGUI::filesDropped(const StringArray& files, int x, int y)
{
	std::cout << "DeckGUI::filesDropped" << std::endl;
	if (files.size() == 1)
	{
		player->loadURL(URL{ File{files[0]} });
	}
}

void DeckGUI::loadTrackToDeck(File file)
{
	player->loadURL(URL{ file });
	waveformDisplay.loadURL(URL{ file });
	trackTitleTxt.setText(player->getTrackDetails()[0]);
	trackDurationTxt.setText(player->getTrackDetails()[1]);
	player->start();

	if (player->isPlaying()) {
		discArt.setRotationSpeed(speedSlider.getValue());
	}
}


void DeckGUI::timerCallback()
{
	waveformDisplay.setPositionRelative(
		player->getPositionRelative());
	levelMeterL.setValue(player->getDecible()[0]);
	levelMeterR.setValue(player->getDecible()[1]);
}
