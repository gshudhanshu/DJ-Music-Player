/*
  ==============================================================================

    PlaylistComponent.h
    Created: 23 Feb 2023 3:03:50pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class PlaylistComponent  : public juce::Component
{
public:
    PlaylistComponent();
    ~PlaylistComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    TableListBox tableComponent;
    TableListBox actions;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistComponent)
};
