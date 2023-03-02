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
DeckGUI::DeckGUI(DJAudioPlayer* _player,
    juce::AudioFormatManager& formatManagerToUse,
    juce::AudioThumbnailCache& cacheToUse)
    : player(_player), waveformDisplay(formatManagerToUse, cacheToUse),
    volumeMeterL(formatManagerToUse, cacheToUse), volumeMeterR(formatManagerToUse, cacheToUse)

{
    // Import svg button SVGs
    auto playSvg = Drawable::createFromImageData(BinaryData::play_solid_svg, BinaryData::play_solid_svgSize);
    auto backwardSvg = Drawable::createFromImageData(BinaryData::backward_solid_svg, BinaryData::backward_solid_svgSize);
    auto forwardSvg = Drawable::createFromImageData(BinaryData::forward_solid_svg, BinaryData::forward_solid_svgSize);
    auto pauseSvg = Drawable::createFromImageData(BinaryData::pause_solid_svg, BinaryData::pause_solid_svgSize);
    auto stopSvg = Drawable::createFromImageData(BinaryData::stop_solid_svg, BinaryData::stop_solid_svgSize);
    auto loopSvg = Drawable::createFromImageData(BinaryData::repeat_solid_svg, BinaryData::repeat_solid_svgSize);

    playButton.setImages(playSvg.get());
    stopButton.setImages(stopSvg.get());
    pauseButton.setImages(pauseSvg.get());
    backwardButton.setImages(backwardSvg.get());
    forwardButton.setImages(forwardSvg.get());
    loopButton.setImages(loopSvg.get());


    highPassSlider.setSliderStyle(juce::Slider::Rotary);
    highPassSlider.setRange(0.0, 1.0);
    highPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

    lowPassSlider.setSliderStyle(juce::Slider::Rotary);
    lowPassSlider.setRange(0.0, 1.0);
    lowPassSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);


    speedSlider.setSliderStyle(juce::Slider::Rotary);
    speedSlider.setRange(0.0, 5.0);
    speedSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);


    volSlider.setSliderStyle(juce::Slider::LinearVertical);
	volSlider.setRange(0.0, 1.0);
    volSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);


    posSlider.setRange(0.0, 1.0);


	trackTitleTxt.setText("Track not loaded");
    trackDurationTxt.setText("00:00");
    trackTitleTxt.isReadOnly();
    trackDurationTxt.isReadOnly();


    addAndMakeVisible(playButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(pauseButton);
    addAndMakeVisible(backwardButton);
    addAndMakeVisible(forwardButton);
    addAndMakeVisible(loopButton);
    addAndMakeVisible(loadButton);

       
    addAndMakeVisible(volumeMeterL);
    addAndMakeVisible(volumeMeterR);
    addAndMakeVisible(volSlider);

    addAndMakeVisible(highPassSlider);
    addAndMakeVisible(lowPassSlider);
    addAndMakeVisible(speedSlider);

    addAndMakeVisible(posSlider);

    addAndMakeVisible(waveformDisplay);
    addAndMakeVisible(trackTitleTxt);
    addAndMakeVisible(trackDurationTxt);


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


    startTimer(500);



}

DeckGUI::~DeckGUI()
{
    stopTimer();
}

void DeckGUI::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("DeckGUI", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
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


    volumeMeterAndVolSlider.items.add(FlexItem(volumeMeterL).withFlex(1));
    volumeMeterAndVolSlider.items.add(FlexItem(volSlider).withFlex(1));
    volumeMeterAndVolSlider.items.add(FlexItem(volumeMeterR).withFlex(1));

    adjKnobs.flexDirection = juce::FlexBox::Direction::column;
    adjKnobs.items.add(FlexItem(lowPassSlider).withFlex(1));
    adjKnobs.items.add(FlexItem(highPassSlider).withFlex(1));
    adjKnobs.items.add(FlexItem(speedSlider).withFlex(1));

	//diskArtAdjKnobsAndVol.items.add(FlexItem(discArt).withFlex(1));
	diskArtAdjKnobsAndVol.items.add(FlexItem().withFlex(5));
    diskArtAdjKnobsAndVol.items.add(FlexItem(adjKnobs).withFlex(1));
    diskArtAdjKnobsAndVol.items.add(FlexItem(volumeMeterAndVolSlider).withFlex(1));


    trackInfo.items.add(FlexItem(trackTitleTxt).withFlex(3));
    trackInfo.items.add(FlexItem(trackDurationTxt).withFlex(1));


    mainGUI.flexDirection = juce::FlexBox::Direction::column;
    mainGUI.items.add(FlexItem(diskArtAdjKnobsAndVol).withFlex(5));
    mainGUI.items.add(FlexItem(trackInfo).withFlex(1));
    mainGUI.items.add(FlexItem(waveformDisplay).withFlex(1));
    mainGUI.items.add(FlexItem(playerButtons).withFlex(1));
	mainGUI.items.add(FlexItem(loadButton).withFlex(1));

    mainGUI.performLayout(getLocalBounds().toFloat());


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
    }
     if (button == &stopButton)
    {
        std::cout << "Stop button was clicked " << std::endl;
        player->stop();

    }
       if (button == &loadButton)
    {
        auto fileChooserFlags = 
        FileBrowserComponent::canSelectFiles;
        fChooser.launchAsync(fileChooserFlags, [this](const FileChooser& chooser)
        {
            player->loadURL(URL{chooser.getResult()});
            // and now the waveformDisplay as well
            waveformDisplay.loadURL(URL{chooser.getResult()});
        });
    }
    // if (button == &loadButton)
    // {
    //     FileChooser chooser{"Select a file..."};
    //     if (chooser.browseForFileToOpen())
    //     {
    //         player->loadURL(URL{chooser.getResult()});
    //         waveformDisplay.loadURL(URL{chooser.getResult()});
            
    //     }


    // }
}

void DeckGUI::sliderValueChanged (Slider *slider)
{
    if (slider == &volSlider)
    {
        player->setGain(slider->getValue());
    }

    if (slider == &speedSlider)
    {
        player->setSpeed(slider->getValue());
    }
    
    if (slider == &posSlider)
    {
        player->setPositionRelative(slider->getValue());
    }
    
}

bool DeckGUI::isInterestedInFileDrag (const StringArray &files)
{
  std::cout << "DeckGUI::isInterestedInFileDrag" << std::endl;
  return true; 
}

void DeckGUI::filesDropped (const StringArray &files, int x, int y)
{
  std::cout << "DeckGUI::filesDropped" << std::endl;
  if (files.size() == 1)
  {
    player->loadURL(URL{File{files[0]}});
  }
}

void DeckGUI::loadTrackToDeck(File file)
{
    player->loadURL(URL{ file });
    waveformDisplay.loadURL(URL{ file });
    trackTitleTxt.setText(player->getTrackDetails()[0]);
    trackDurationTxt.setText(player->getTrackDetails()[1]);
}


void DeckGUI::timerCallback()
{
    //std::cout << "DeckGUI::timerCallback" << std::endl;
    waveformDisplay.setPositionRelative(
    player->getPositionRelative());
    volumeMeterL.repaint();
    volumeMeterR.repaint();
    DBG("test");
}

    
//void DeckGUI::setTrackDetails(String title, int seconds)
//{
//    trackTitleTxt.setText(title);
//    int hr = (seconds / 3600);
//    int min = (seconds / 60) % 60;
//    int sec = (seconds % 60);
//    String time = String(hr) + ":" + String(min) + ":" + String(sec);
//    trackTitleTxt.setText(time);
//}
//
