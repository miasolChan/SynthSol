

#include <JuceHeader.h>
#include "ReverbComponent.h"

//==============================================================================
ReverbComponent::ReverbComponent(juce::AudioProcessorValueTreeState& apvts, juce::String reverbRoomID,
    juce::String reverbDampID, juce::String reverbWetID, juce::String reverbDryID,
    juce::String reverbWidthID, juce::String reverbFreezeID)
{
    setSliderWithLabel(roomSizeSlider, roomSizeLabel, apvts, reverbRoomID,roomSizeSliderAttachment,"Size");
    setSliderWithLabel(dampingSlider, dampingLabel, apvts, reverbDampID, dampingSliderAttachment,"Damp");
    setSliderWithLabel(wetSlider, wetLabel, apvts, reverbWetID, wetSliderAttachment,"Wet");
    setSliderWithLabel(drySlider, dryLabel, apvts, reverbDryID, drySliderAttachment,"Dry");
    setSliderWithLabel(widthSlider, widthLabel, apvts, reverbWidthID, widthSliderAttachment,"Width");
    setSliderWithLabel(freezeSlider, freezeLabel, apvts, reverbFreezeID, freezeSliderAttachment,"Freeze");
}

ReverbComponent::~ReverbComponent()
{
}

void ReverbComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(CustomColours::grey);
    g.setFont(20.0f);
    g.drawText("Reverb", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 260, 
        bounds.getHeight()-60, 5.0f, 5.0f);

    g.setColour(CustomColours::black);
    g.fillRoundedRectangle(bounds.getX(), bounds.getY(), bounds.getWidth() - 260,
        bounds.getHeight()-60, 5.0f);

}

void ReverbComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 70;
    const auto sliderHeight = 70;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    roomSizeSlider.setBounds(10, startYPos, sliderWidth, sliderHeight);
    roomSizeLabel.setBounds(roomSizeSlider.getX(), roomSizeSlider.getY() - labelYOffset,
        roomSizeSlider.getWidth(), labelHeight);
    dampingSlider.setBounds(roomSizeSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    dampingLabel.setBounds(dampingSlider.getX(), dampingSlider.getY() - labelYOffset,
        dampingSlider.getWidth(), labelHeight);
    wetSlider.setBounds(dampingSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    wetLabel.setBounds(wetSlider.getX(), wetSlider.getY() - labelYOffset,
        wetSlider.getWidth(), labelHeight);
    drySlider.setBounds(wetSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    dryLabel.setBounds(drySlider.getX(), drySlider.getY() - labelYOffset,
        drySlider.getWidth(), labelHeight);
    widthSlider.setBounds(drySlider.getRight(), startYPos, sliderWidth, sliderHeight);
    widthLabel.setBounds(widthSlider.getX(), widthSlider.getY() - labelYOffset,
        widthSlider.getWidth(), labelHeight);
    freezeSlider.setBounds(widthSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    freezeLabel.setBounds(freezeSlider.getX(), freezeSlider.getY() - labelYOffset,
        freezeSlider.getWidth(), labelHeight);
}


using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void ReverbComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment,juce::String text)
{
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
    label.setText(text, juce::NotificationType::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}