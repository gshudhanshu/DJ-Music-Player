/*
  ==============================================================================

	MyLookAndFeel.h
	Created: 9 Mar 2023 1:59:52am
	Author:  Shudhanshu Gunjal

	Taking reference from following github repository, using knobs from g200kg.com gallary, and Knobman software to edit the knobs:
	- https://github.com/remberg/juceCustomSliderSample
	- https://www.g200kg.com/en/webknobman/gallery.php
	- Knobman software is used to create/modify the images for the sliders

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

// Custom LookAndFeel for a rotary slider control
class MyRotarySliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    // Constructor that takes a pointer to a string indicating the side (A or B) of the slider
    MyRotarySliderLookAndFeel(String* _side);

    // customize the appearance of the rotary slider
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;

    // customize the layout of the slider
    void getSliderLayout(juce::Slider& slider, juce::Slider::SliderLayout& layout);

private:
    // Pointer to a string indicating the side (A or B) of the slider
    String* side;

    // Image of the knob used for the slider
    juce::Image knob;
};


// Custom LookAndFeel for a linear slider control
class MySliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
    // Constructor that takes a pointer to a string indicating the side (A or B) of the slider
    MySliderLookAndFeel(String* _side);

    // Customize the appearance of the linear slider
    void drawLinearSlider(Graphics& g, int x, int y, int width, int height, float sliderPos,
        float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider) override;

private:
    // Pointer to a string indicating the side (A or B) of the slider
    String* side;

    // Image of the slider thumb and background
    Image sliderThumbImage, sliderBackgroundImage;
};


// Custom LookAndFeel for buttons
class MyLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MyLookAndFeel();

    // Customize the appearance of buttons
    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
        bool isMouseOverButton, bool isButtonDown) override;
};
