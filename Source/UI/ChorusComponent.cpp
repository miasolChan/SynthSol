

#include <JuceHeader.h>
#include "ChorusComponent.h"

//==============================================================================
ChorusComponent::ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
    juce::String depthID, juce::String centerDelayID, juce::String fdbkID, juce::String mixID)
{
    setSliderWithLabel(rateSlider, rateLabel, apvts, rateID, rateSliderAttachment, "Rate");
    setSliderWithLabel(depthSlider, depthLabel, apvts, depthID, depthSliderAttachment,"Depth");
    setSliderWithLabel(centerDelaySlider, centerDelayLabel, apvts, centerDelayID, centerDelaySliderAttachment,"Delay");
    setSliderWithLabel(fdbkSlider, fdbkLabel, apvts, fdbkID, fdbkSliderAttachment, "Fdbk");
    setSliderWithLabel(mixSlider, mixLabel, apvts, mixID, mixSliderAttachment,"Mix");
}

ChorusComponent::~ChorusComponent()
{
}

void ChorusComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(CustomColours::grey);
    g.setFont(20.0f);
    g.drawText("Chorus", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 310,
        bounds.getHeight() - 60, 5.0f, 5.0f);

    g.setColour(CustomColours::black);
    g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 310,
        bounds.getHeight() - 60, 5.0f);
}

void ChorusComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 70;
    const auto sliderHeight = 70;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    rateSlider.setBounds(10, startYPos, sliderWidth, sliderHeight);
    rateLabel.setBounds(rateSlider.getX(), rateSlider.getY() - labelYOffset,
        rateSlider.getWidth(), labelHeight);
    depthSlider.setBounds(rateSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    depthLabel.setBounds(depthSlider.getX(), depthSlider.getY() - labelYOffset,
        depthSlider.getWidth(), labelHeight);
    centerDelaySlider.setBounds(depthSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    centerDelayLabel.setBounds(centerDelaySlider.getX(), centerDelaySlider.getY() - labelYOffset,
        centerDelaySlider.getWidth(), labelHeight);
    fdbkSlider.setBounds(centerDelaySlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fdbkLabel.setBounds(fdbkSlider.getX(), fdbkSlider.getY() - labelYOffset,
        fdbkSlider.getWidth(), labelHeight);
    mixSlider.setBounds(fdbkSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    mixLabel.setBounds(mixSlider.getX(), mixSlider.getY() - labelYOffset,
        mixSlider.getWidth(), labelHeight);
}


using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void ChorusComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text)
{
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
    label.setText(text, juce::NotificationType::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}