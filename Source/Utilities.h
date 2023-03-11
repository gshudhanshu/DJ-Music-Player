/*
  ==============================================================================

    Utilities.h
    Created: 11 Mar 2023 10:31:31pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Utilities  : public juce::Component
{
public:
    Utilities();
    ~Utilities() override;

    // Convert seconds to hh:mm:ss format string
    String convertSecTohhmmssFormat(int seconds);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Utilities)
};
