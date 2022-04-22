

#include "Dial.h"

Dial::Dial()
{
    setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    setTextBoxStyle(juce::Slider::TextBoxBelow, false, 80, 20);
    setRotaryParameters(juce::MathConstants<float>::pi * 1.25f,
        juce::MathConstants<float>::pi * 2.75f,
        true);
    setColour(juce::Slider::textBoxTextColourId, CustomColours::creamWhite);
    setColour(juce::Slider::textBoxOutlineColourId, CustomColours::grey);
    setColour(juce::Slider::rotarySliderFillColourId, CustomColours::blue);
    //lookandfeel
    setColour(juce::Slider::textBoxTextColourId, CustomColours::black);
    setLookAndFeel(&customLookAndFeel);
    //  Û±Í/¡¶∂»
    setVelocityBasedMode(true);
    //¡È√Ù∂»
    setVelocityModeParameters(1.0, 1, 0.1, false);
    setRange(0.0, 100.0, 0.01);
    setValue(50.0);
    setDoubleClickReturnValue(true, 50.0);
    setTextValueSuffix("");
    //œ‘ æ∑∂Œß
    onValueChange = [&]()
    {
        if (getValue() < 10)
            setNumDecimalPlacesToDisplay(2);
        else if (10 <= getValue() && getValue() < 100)
            setNumDecimalPlacesToDisplay(1);
        else
            setNumDecimalPlacesToDisplay(0);
    };

    //æ€Ωπ
    setWantsKeyboardFocus (true);
}
void Dial::paint(juce::Graphics& g)
{
    juce::Slider::paint(g);

    if (hasKeyboardFocus(true))
    {
        auto bounds = getLocalBounds().toFloat();
        auto len = juce::jmin(bounds.getHeight(), bounds.getWidth()) * 0.07f;
        auto thick = len * 0.5f;

        auto topLeft = bounds.getTopLeft();
        auto topRight = bounds.getTopRight();
        auto bottomLeft = bounds.getBottomLeft();
        auto bottomRight = bounds.getBottomRight();

        g.setColour(findColour(juce::Slider::textBoxOutlineColourId));

        juce::Path topLeftPath;
        topLeftPath.startNewSubPath(topLeft);
        topLeftPath.lineTo(topLeft.x, topLeft.y + len);
        topLeftPath.startNewSubPath(topLeft);
        topLeftPath.lineTo(topLeft.x + len, topLeft.y);
        g.strokePath(topLeftPath, juce::PathStrokeType(thick));

        juce::Path topRightPath;
        topRightPath.startNewSubPath(topRight);
        topRightPath.lineTo(topRight.x, topRight.y + len);
        topRightPath.startNewSubPath(topRight);
        topRightPath.lineTo(topRight.x - len, topRight.y);
        g.strokePath(topRightPath, juce::PathStrokeType(thick));

        juce::Path bottomLeftPath;
        bottomLeftPath.startNewSubPath(bottomLeft);
        bottomLeftPath.lineTo(bottomLeft.x, bottomLeft.y - len);
        bottomLeftPath.startNewSubPath(bottomLeft);
        bottomLeftPath.lineTo(bottomLeft.x + len, bottomLeft.y);
        g.strokePath(bottomLeftPath, juce::PathStrokeType(thick));

        juce::Path bottomRightPath;
        bottomRightPath.startNewSubPath(bottomRight);
        bottomRightPath.lineTo(bottomRight.x, bottomRight.y - len);
        bottomRightPath.startNewSubPath(bottomRight);
        bottomRightPath.lineTo(bottomRight.x - len, bottomRight.y);
        g.strokePath(bottomRightPath, juce::PathStrokeType(thick));
    }
}

bool Dial::keyPressed(const juce::KeyPress& k)
{
    char numChars[] = "0123456789";

    for (auto numChar : numChars)
    {
        if (k.isKeyCode(numChar))
        {
            CustomLookAndFeel::CustomLabel::initialPressedKey = juce::String::charToString(numChar);
            showTextBox();

            return true;
        }
    }

    return false;
}

void Dial::mouseDown(const juce::MouseEvent& event)
{
    juce::Slider::mouseDown(event);

    setMouseCursor(juce::MouseCursor::NoCursor);
}

void Dial::mouseUp(const juce::MouseEvent& event)
{
    juce::Slider::mouseUp(event);

    juce::Desktop::getInstance().getMainMouseSource().setScreenPosition(event.source.getLastMouseDownPosition());

    setMouseCursor(juce::MouseCursor::NormalCursor);
}

Dial::~Dial()
{
    setLookAndFeel(nullptr);
}