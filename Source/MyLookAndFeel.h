/*
  ==============================================================================

	MyLookAndFeel.h
	Created: 9 Mar 2023 1:59:52am
	Author:  Shudhanshu Gunjal

	Taking reference from following github repository, using knobs from g200kg.com gallary, and using Knobman software to edit the knobs:
	- https://github.com/remberg/juceCustomSliderSample
	- https://www.g200kg.com/en/webknobman/gallery.php
	- Knobman software is used to create/modify the images for the rotary slider

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class MyRotarySliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
	MyRotarySliderLookAndFeel(String* _side) : side(_side)
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
	void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
		const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
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
		else
		{
			static const float textPpercent = 0.35f;
			Rectangle<float> text_bounds(1.0f + width * (1.0f - textPpercent) / 2.0f, 0.5f * height, width * textPpercent, 0.5f * height);

			g.setColour(Colours::white);

			g.drawFittedText(String("No Image"), text_bounds.getSmallestIntegerContainer(),
				Justification::horizontallyCentred | Justification::centred, 1);
		}
	}

	void getSliderLayout(juce::Slider& slider, juce::Slider::SliderLayout& layout)
	{
		// call the base class to get the default layout
		LookAndFeel_V4::getSliderLayout(slider);

		// add padding to the layout
		layout.sliderBounds = layout.sliderBounds.reduced(50);
	}

private:
	String* side;
	Image knob;
};

class MySliderLookAndFeel : public juce::LookAndFeel_V4
{
public:
	MySliderLookAndFeel(String* _side) : side(_side)
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

	void drawLinearSlider(Graphics& g, int x, int y, int width, int height,
		float sliderPos, float minSliderPos, float maxSliderPos,
		const Slider::SliderStyle style, Slider& slider) override
	{
		const int lineThickness = 4;
		const int dialWidth = sliderThumbImage.getWidth();
		const int dialHeight = sliderThumbImage.getHeight();

		//g.drawImageAt(sliderThumbImage, (width - dialWidth) / 2.f, sliderPos - (dialHeight / 2));

		const float padding = 10.0f;
		const float destWidth = width;
		const float destHeight = height*0.5;
		const float centerX = x + destWidth * 0.5f;
		const float centerY = y + destHeight * 0.5f - 8.0f;
		const float rx = centerX - destWidth/2 - 1.0f;
		const float ry = centerY;

		if (*side == String("A"))
		{
			g.setColour(Colour(252,183,67));
		} else
		{
			g.setColour(Colour(74, 244, 210));
		}
		g.fillRect(((int)destWidth - lineThickness) / 2, (int)destHeight / 2 - 8.0, lineThickness, height);

		g.setColour(Colours::black);
		g.fillRect(((int)destWidth - lineThickness) / 2, (int)destHeight / 2 - 8.0, lineThickness, (int)sliderPos);

		g.drawImage(sliderThumbImage, (int)rx, sliderPos-(int)ry,  (int)destWidth,  (int)destHeight,
			0, 0, dialWidth, dialHeight);

	}

private:
	String* side;
	Image sliderThumbImage, sliderBackgroundImage;

};

class MyTextButtonLookAndFeel : public juce::LookAndFeel_V4
{
public:
	MyTextButtonLookAndFeel()
	{
		// Set default colors for text button
		setColour(TextButton::buttonColourId, Colour(0xff282a36)); // Blue-black background
		setColour(TextButton::textColourOnId, Colours::orange); // Orange text
		//setColour(TextButton::outlineColourId, Colours::orange); // Orange border
	}

	void drawButtonBackground(Graphics & g, Button & button, const Colour & backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override
	{
		LookAndFeel_V4::drawButtonBackground(g, button, backgroundColour, isMouseOverButton, isButtonDown);

		if (isButtonDown)
		{
			g.setColour(Colours::orange); // Set background color when button is pressed
			g.fillRect(button.getLocalBounds());
		}
	}
	
};


//class MyDrawableButtonLookAndFeel : public juce::LookAndFeel_V4
//{
//public:
//    MyDrawableButtonLookAndFeel();
//    void drawButtonBackground(juce::Graphics& g, juce::Button& button, const juce::Colour& backgroundColour,
//        bool isMouseOverButton, bool isButtonDown) override;
//
//    void drawButtonText(juce::Graphics& g, juce::TextButton& button, bool isMouseOverButton, bool isButtonDown) override;
//
//    void drawToggleButton(juce::Graphics& g, juce::ToggleButton& toggleButton, bool isMouseOverButton, bool isButtonDown) override;
//};
//
//class MyTableLookAndFeel : public juce::LookAndFeel_V4
//{
//public:
//    MyTableLookAndFeel();
//    void drawTableHeader(juce::Graphics& g, const juce::TableHeaderComponent& header) override;
//
//    void drawTableRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
//
//    void drawTableHeaderBackground(juce::Graphics& g, juce::TableHeaderComponent& header) override;
//
//    void drawTableHeaderColumn(juce::Graphics& g, const juce::String& columnName,
//        int columnId, int width, int height, bool isMouseOver, bool isMouseDown,
//        int columnFlags) override;
//
//    void drawTableListBoxRow(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected,
//        juce::TableListBox& table) override;
//
//    void drawTableListBoxBackground(juce::Graphics& g, juce::TableListBox& tableListBox) override;
//};
//
//


class MyResizableWindowLookAndFeel : public LookAndFeel_V4
{
public:
	MyResizableWindowLookAndFeel()
	{
		setColour(ResizableWindow::backgroundColourId, Colour(0xff1e253a)); 
		setColour(TableHeaderComponent::backgroundColourId, Colour(0xff1e253a));

		setColour(TextButton::buttonColourId, Colour(0xff1e253a));
		setColour(TextButton::textColourOffId, Colour(0xffffffff));

		setColour(TextButton::textColourOnId, Colour(0xfffcb743));

		setColour(TableHeaderComponent::textColourId, Colour(0xffffffff));
	}


};