

#include <JuceHeader.h>
#include "CompressorComponent.h"

//==============================================================================
CompressorComponent::CompressorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String thresholdID,
    juce::String ratioID, juce::String attackID, juce::String releaseID)
{
    setSliderWithLabel(thresholdSlider, thresholdLabel, apvts, thresholdID, thresholdSliderAttachment,"Threshold");
    setSliderWithLabel(ratioSlider, ratioLabel, apvts, ratioID, ratioSliderAttachment,"Ratio");
    setSliderWithLabel(attackSlider, attackLabel, apvts, attackID, attackSliderAttachment,"Attack");
    setSliderWithLabel(releaseSlider, releaseLabel, apvts, releaseID, releaseSliderAttachment,"Release");
}

CompressorComponent::~CompressorComponent()
{
}

void CompressorComponent::paint (juce::Graphics& g)
{

    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(CustomColours::grey);
    g.setFont(20.0f);
    g.drawText("Compressor", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 310,
        bounds.getHeight() - 60, 5.0f, 5.0f);

    g.setColour(CustomColours::black);
    g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 310,
        bounds.getHeight() - 60, 5.0f);
}

void CompressorComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 70;
    const auto sliderHeight = 70;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    thresholdSlider.setBounds(10, startYPos, sliderWidth, sliderHeight);
    thresholdLabel.setBounds(thresholdSlider.getX(), thresholdSlider.getY() - labelYOffset,
        thresholdSlider.getWidth(), labelHeight);
    ratioSlider.setBounds(thresholdSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    ratioLabel.setBounds(ratioSlider.getX(), ratioSlider.getY() - labelYOffset,
        ratioSlider.getWidth(), labelHeight);
    attackSlider.setBounds(ratioSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    attackLabel.setBounds(attackSlider.getX(), attackSlider.getY() - labelYOffset,
        attackSlider.getWidth(), labelHeight);
    releaseSlider.setBounds(attackSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getY() - labelYOffset,
        releaseSlider.getWidth(), labelHeight);
}

void CompressorComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text)
{
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
    label.setText(text, juce::NotificationType::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}
