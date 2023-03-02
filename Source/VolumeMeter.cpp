/*
  ==============================================================================

    VolumeMeter.cpp
    Created: 2 Mar 2023 12:45:08pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include <JuceHeader.h>
#include "VolumeMeter.h"

//==============================================================================
VolumeMeter::VolumeMeter(AudioFormatManager& formatManagerToUse,
    AudioThumbnailCache& cacheToUse)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    startTimerHz(24);
    //grill = ImageCache::getFromMemory(BinaryData::MeterGrill_png, BinaryData::MeterGrill_pngSize);

}

VolumeMeter::~VolumeMeter()
{
}

void VolumeMeter::paint (juce::Graphics& g)
{
    //const auto level = valueSupplier();
    const auto level = -20.0f;

    auto bounds = getLocalBounds().toFloat().reduced(2.f);

    g.setColour(Colours::black);
    g.fillRect(bounds);

    g.setGradientFill(gradient);
    const auto scaledY =
        jmap(level, -60.f, 6.f, 0.f, static_cast<float>(getHeight()));
    g.fillRect(bounds.removeFromBottom(scaledY));

}

void VolumeMeter::resized()
{
    const auto bounds = getLocalBounds().toFloat();
    gradient = ColourGradient{
            Colours::green,
            bounds.getBottomLeft(),
            Colours::red,
            bounds.getTopLeft(),
            false
    };
    gradient.addColour(0.5, Colours::yellow);

}

void VolumeMeter::timerCallback()
{
    repaint();
}
