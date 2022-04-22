

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveID, juce::String fmFreqID, 
    juce::String fmDepthID,juce::String  fmPitchID, juce::String fmGainID)
{
    juce::StringArray waveChoices = { "Sine", "Saw", "Square", "White Noise" };
    waveformSelector.addItemList(waveChoices, 1);
    addAndMakeVisible(waveformSelector);

    oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveID, waveformSelector);

    waveformLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::black);
    //waveformLabel.setFont(15.0f);
    //waveformLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(waveformLabel);

    setSliderWithLabel(fmFrequencySlider, fmFrequencyLabel, apvts, fmFreqID, fmFrequencySliderAttachment,"Freq");
    setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthID, fmDepthSliderAttachment,"Depth");
    setSliderWithLabel(fmPitchSlider, fmPitchLabel, apvts, fmPitchID, fmDepthSliderAttachment, "Pitch");
    setSliderWithLabel(fmGainSlider, fmGainLabel, apvts, fmGainID, fmDepthSliderAttachment, "Gain");
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(CustomColours::grey);
    g.setFont(20.0f);
    g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 5.0f);
    g.setColour(CustomColours::black);
    g.fillRoundedRectangle(bounds.toFloat(), 5.0f);
}

void OscComponent::resized()
{
    const auto startYPos = 55;
    const auto sliderWidth = 70;
    const auto sliderHeight = 70;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    waveformSelector.setBounds(10, startYPos + 5, 90, 30);
    waveformLabel.setBounds(10, startYPos - labelYOffset, 90, labelHeight);
    
    fmFrequencySlider.setBounds(waveformSelector.getRight(), startYPos, sliderWidth, sliderHeight);
    fmFrequencyLabel.setBounds(fmFrequencySlider.getX(), fmFrequencySlider.getY() - labelYOffset,fmFrequencySlider.getWidth(), labelHeight);

    fmDepthSlider.setBounds(fmFrequencySlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset,fmDepthSlider.getWidth(), labelHeight);

    fmPitchSlider.setBounds(fmDepthSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fmPitchLabel.setBounds(fmPitchSlider.getX(), fmPitchSlider.getY() - labelYOffset, fmPitchSlider.getWidth(), labelHeight);

    fmGainSlider.setBounds(fmPitchSlider.getRight(), startYPos, sliderWidth, sliderHeight);
    fmGainLabel.setBounds(fmGainSlider.getX(), fmGainSlider.getY() - labelYOffset, fmGainSlider.getWidth(), labelHeight);



}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text)
{
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);
    label.setText(text, juce::NotificationType::dontSendNotification);
    label.attachToComponent(&slider, false);
    addAndMakeVisible(slider);
    addAndMakeVisible(label);
}