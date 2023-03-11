/*
  ==============================================================================

    Utilities.cpp
    Created: 11 Mar 2023 10:31:31pm
    Author:  Shudhanshu Gunjal

  ==============================================================================
*/

#include "Utilities.h"

//==============================================================================
Utilities::Utilities()
{

}

Utilities::~Utilities()
{
}


String Utilities::convertSecTohhmmssFormat(int seconds)
{
	String hr0, min0, sec0;
	int hr = (seconds / 3600);
	int min = (seconds / 60) % 60;
	int sec = (seconds % 60);
	if (hr < 10) {
		hr0 = "0";
	}
	if (min < 10) {
		min0 = "0";
	}
	if (sec < 10) {
		sec0 = "0";
	}

	String hourString;
	if (hr0 + String(hr) == "00")
	{
		hourString = "";
	}
	else
	{
		hourString = hr0 + String(hr) + ":";
	}

	String time = hourString + min0 + String(min) + ":" + sec0 + String(sec);
	return time;
}