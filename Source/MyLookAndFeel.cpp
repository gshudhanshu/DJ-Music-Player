/*
  ==============================================================================

    MyLookAndFeel.cpp
    Created: 9 Mar 2023 1:59:52am
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include "MyLookAndFeel.h"

MyRotarySliderLookAndFeel::MyRotarySliderLookAndFeel(String* _side) : side(_side)
{
    if (*side == String("A"))
    {
        knob = ImageCache::getFromMemory(BinaryData::orange_knob_png, BinaryData::orange_knob_pngSize);
    }
    else
    {
        knob = ImageCache::getFromMemory(BinaryData::cyan_knob_png, BinaryData::cyan_knob_pngSize);
    }
}

void MyRotarySliderLookAndFeel::drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
    const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider)
{
    if (knob.isValid())
    {
        const double rotation = (slider.getValue() - slider.getMinimum()) / (slider.getMaximum() - slider.getMinimum());
        const int frames = knob.getHeight() / knob.getWidth();
        const int frameId = (int)ceil(rotation * ((double)frames - 1.0));
        const float padding = 5.0f;
        const float radius = jmin(width / 2.0f - padding, height / 2.0f - padding);
        const float centerX = x + width * 0.5f;
        const float centerY = y + height * 0.5f;
        
    	const float rx = centerX - radius - 1.0f;
        const float ry = centerY - radius;

        g.drawImage(knob, (int)rx, (int)ry, 2 * (int)radius, 2 * (int)radius,
            0, frameId * knob.getWidth(), knob.getWidth(), knob.getWidth());
    }

	// if the knob image is not valid, shows a text instead of the knob
    else
    {
        static const float textPercent = 0.35f;
        Rectangle<float> text_bounds(1.0f + width * (1.0f - textPercent) / 2.0f, 0.5f * height, width * textPercent, 0.5f * height);

        g.setColour(Colours::white);

        g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
            Justification::horizontallyCentred | Justification::centred, 1);
    }
}

void MyRotarySliderLookAndFeel::getSliderLayout(juce::Slider& slider, juce::Slider::SliderLayout& layout)
{
    // call the base class to get the default layout
    LookAndFeel_V4::getSliderLayout(slider);

    // add padding to the layout
    layout.sliderBounds = layout.sliderBounds.reduced(50);
}



MySliderLookAndFeel::MySliderLookAndFeel(String* _side) : side(_side)
{
    if (*side == String("A"))
    {
        sliderThumbImage = ImageCache::getFromMemory(BinaryData::orange_slider_png, BinaryData::orange_slider_pngSize);
    }
    else
    {
        sliderThumbImage = ImageCache::getFromMemory(BinaryData::cyan_slider_png, BinaryData::cyan_slider_pngSize);
    }
}

void MySliderLookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
    float sliderPos, float minSliderPos, float maxSliderPos, const Slider::SliderStyle style, Slider& slider)
{
    const int lineThickness = 4;
    const int dialWidth = sliderThumbImage.getWidth();
    const int dialHeight = sliderThumbImage.getHeight();

    const float padding = 10.0f;
    const float destWidth = width;
    const float destHeight = height * 0.5;
    const float centerX = x + destWidth * 0.5f;
    const float centerY = y + destHeight * 0.5f - 8.0f;
    const float rx = centerX - destWidth / 2 - 1.0f;
    const float ry = centerY;

    // If the slider is for deck A then set the colour to orange else set it to cyan
    if (*side == String("A"))
    {
        g.setColour(Colour(252, 183, 67));
    }
    else
    {
        g.setColour(Colour(74, 244, 210));
    }

    // Draw the slider with respective theme color
    g.fillRect(((int)destWidth - lineThickness) / 2, (int)destHeight / 2 - 8.0, lineThickness, height);

    g.setColour(Colours::black);
    // draw black slider backround
    g.fillRect(((int)destWidth - lineThickness) / 2, (int)destHeight / 2 - 8.0, lineThickness, (int)sliderPos);

    // draw the slider thumb
    g.drawImage(sliderThumbImage, (int)rx, sliderPos - (int)ry, (int)destWidth, (int)destHeight,
        0, 0, dialWidth, dialHeight);
}



MyLookAndFeel::MyLookAndFeel()
{
    setColour(juce::ResizableWindow::backgroundColourId, juce::Colour(0xff1e253a));
    setColour(juce::TableHeaderComponent::backgroundColourId, juce::Colour(0xff1e253a));

    setColour(juce::ListBox::backgroundColourId, juce::Colours::grey);
    setColour(juce::ListBox::textColourId, juce::Colours::white);
    setColour(juce::ListBox::outlineColourId, juce::Colours::orange);

    setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff1e253a));

    setColour(juce::TextButton::buttonColourId, juce::Colour(0xff1e253a));
    setColour(juce::TextButton::textColourOffId, juce::Colour(0xffffffff));

    setColour(juce::TableHeaderComponent::textColourId, juce::Colour(0xffffffff));
}

void MyLookAndFeel::drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
    bool isMouseOverButton, bool isButtonDown)
{
    LookAndFeel_V4::drawButtonBackground(g, button, backgroundColour, isMouseOverButton, isButtonDown);

    g.setColour(backgroundColour);
    g.fillRect(button.getLocalBounds());
    g.setColour(juce::Colours::grey);
    g.drawRect(button.getLocalBounds(), 1);

    if (isButtonDown)
    {
        g.setColour(juce::Colours::grey); // Set background color when button is pressed
        g.fillRect(button.getLocalBounds());
    }
}
