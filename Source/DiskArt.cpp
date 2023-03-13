/*
  ==============================================================================

    DiscArt.cpp
    Created: 2 Mar 2023 12:46:56pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DiskArt.h"

//==============================================================================
DiskArt::DiskArt(DJAudioPlayer* _player) : player(_player)
{
    startTimerHz(60);
}

DiskArt::~DiskArt()
{
}

void DiskArt::paint (juce::Graphics& g)
{

    const float centerX = getWidth() / 2.0f;
    const float centerY = getHeight() / 2.0f;
    const float radius = jmin(centerX, centerY) - 10.0f;
    const int numSlices = 30;
    const float sliceAngle = MathConstants<float>::twoPi / numSlices;

    // Add a glow effect (circles) to the music disk
    const float glowRadius = radius * 1.5f;
    const Colour glowColour = Colours::white.withAlpha(0.2f);
    const int numGlowCircles = 10;
    const float glowCircleSpacing = glowRadius / numGlowCircles;
    g.setColour(glowColour);
    g.saveState();
    g.addTransform(AffineTransform::rotation(rotationAngle, centerX, centerY));


    for (int i = 1; i <= numGlowCircles; ++i)
    {
        const float circleRadius = i * glowCircleSpacing;
        const float circleAlpha = 0.8f - 0.6f * static_cast<float>(i) / numGlowCircles;
        const Colour circleColour = glowColour.withAlpha(circleAlpha);
        g.setColour(circleColour);
        g.drawEllipse(centerX - circleRadius, centerY - circleRadius, 2.0f * circleRadius, 2.0f * circleRadius, 1.0f);
    }
    g.restoreState();


    // Defining the start and end colors for the slices
    Colour startColor = primaryColor;
    Colour endColor = Colour::fromHSV(primaryColor.getHue() -0.05, 1.0f, 0.9f, 1.0f); // offset color

    // Drawing the slices of the music disk
    Path slicePath;
    for (int i = 0; i < numSlices; ++i)
    {
        const float startAngle = i * sliceAngle;
        const float endAngle = (i + 1) * sliceAngle;

        // Calculating the slice color by interpolating between the start and end colors
        float position = static_cast<float>(i) / numSlices;
        Colour sliceColour = startColor.interpolatedWith(endColor, position);
        
        slicePath.clear();
        slicePath.startNewSubPath(centerX, centerY);
        slicePath.addPieSegment(centerX - radius, centerY - radius, 2.0f * radius, 2.0f * radius, startAngle, endAngle, 0.0f);
        g.setColour(sliceColour);
        g.saveState();
        g.addTransform(AffineTransform::rotation(rotationAngle, centerX, centerY));
        g.fillPath(slicePath);
        g.restoreState();
    }

    // Drawing the center hole of the music disk
    const float holeRadius = radius / 5.0f;
    const Colour holeColour = Colours::black;
    g.setColour(holeColour);
    g.fillEllipse(centerX - holeRadius, centerY - holeRadius, 2.0f * holeRadius, 2.0f * holeRadius);

}

void DiskArt::resized()
{

}

void DiskArt::timerCallback()
{
    rotationAngle += rotationSpeed;
    if (rotationAngle >= 360.0f)
        rotationAngle = 0.0f;
    if (primaryColor.getBrightness() <= 0) { primaryColor = player->getPlayerColour(); }
    repaint();
}


void DiskArt::setRotationSpeed(float factor)
{
    rotationSpeed = 0.05*factor;
}
