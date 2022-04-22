

#include <JuceHeader.h>
#include "GainComponent.h"

//==============================================================================
GainComponent::GainComponent(juce::AudioProcessorValueTreeState& apvts, juce::String gainID)
{
    setSliderWithLabel(gainSlider, gainLabel, apvts, gainID, gainSliderAttachment,"Volume");

}

GainComponent::~GainComponent()
{
}

void GainComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(CustomColours::grey);
    g.setFont(20.0f);
    g.drawText("Gain", labelSpace.withX(5), juce::Justification::left);
    //g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(),bounds.getHeight(), 5.0f, 5.0f);
    g.setColour(CustomColours::black);
    g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth(),
        bounds.getHeight(), 5.0f);
}

void GainComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 70;
    const auto sliderHeight = 70;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    gainSlider.setBounds(10, startYPos, sliderWidth, sliderHeight);
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - labelYOffset,
        gainSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void GainComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text)
{
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
    label.setText(text, juce::NotificationType::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}