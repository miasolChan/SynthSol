
#pragma once
#include <JuceHeader.h>
#include"CustomColours.h"
class NameLabel : public juce::Label
{
public:
	NameLabel()
	{
		setFont(15.f);
		setColour(juce::Label::textColourId,CustomColours::creamWhite );
		setJustificationType(juce::Justification::centred);
	}

	~NameLabel() {}

private:
	juce::Colour grey = juce::Colour::fromFloatRGBA(0.42f, 0.42f, 0.42f, 1.0f);

};