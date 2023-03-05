/*
  ==============================================================================

    DiscArt.cpp
    Created: 2 Mar 2023 12:46:56pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DiscArt.h"

//==============================================================================
DiscArt::DiscArt()
{
    mDiscColour = Colours::blue;
    mRotationAngle = 0.0f;
    startTimerHz(60);
}

DiscArt::~DiscArt()
{
}

void DiscArt::paint (juce::Graphics& g)
{
    g.fillAll(Colours::white); // Fill the background with white
    //g.setGradientFill(ColourGradient(mDiscColour.darker(), mDiscColour.brighter(), getLocalBounds().getCentre().toFloat(), mDiscColour, true)); // Set the gradient fill of the disc
    g.fillEllipse(getLocalBounds().toFloat()); // Draw the disc
    g.setColour(Colours::black); // Set the color of the border
    //g.setThickness(3.0f); // Set the thickness of the border
    g.drawEllipse(getLocalBounds().toFloat(), 3.0f); // Draw the border

}

void DiscArt::resized()
{
    // Set the center point of the disc to the center of the component
    mCenterX = getWidth() / 2.0f;
    mCenterY = getHeight() / 2.0f;

}

void DiscArt::timerCallback()
{
//    mRotationAngle += 0.5f;
//    if (mRotationAngle >= 360.0f)
//        mRotationAngle = 0.0f;
//    setTransform(AffineTransform::rotation(mRotationAngle * MathConstants<float>::pi / 180.0f, getWidth() / 2.0f, getHeight() / 2.0f));
}


void DiscArt::setDiscColour(Colour newColour)
{
    mDiscColour = newColour;
}

void DiscArt::setRotationSpeed(float newSpeed)
{
    mRotationSpeed = newSpeed;
}
