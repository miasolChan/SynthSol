

#pragma once

#include "CustomColours.h"
#include <JuceHeader.h>
#include "CustomLookAndFeel.h"
class Dial : public juce::Slider
{
public:
    Dial();
    ~Dial();

    void paint(juce::Graphics& g) override;

    bool keyPressed(const juce::KeyPress& k) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseUp(const juce::MouseEvent& event) override;
private:
    CustomLookAndFeel customLookAndFeel;
};