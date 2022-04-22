

#pragma once

#include <JuceHeader.h>
#include"LookAndFeel/Dial.h"
#include"LookAndFeel/NameLabel.h"
#include"LookAndFeel/CustomColours.h"
//==============================================================================
/*
*/
class ChorusComponent  : public juce::Component
{
public:
    ChorusComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
        juce::String depthID, juce::String centerFreqID, juce::String fdbkID, juce::String mixID);
    ~ChorusComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text);

    Dial rateSlider;
    Dial depthSlider;
    Dial centerDelaySlider;
    Dial fdbkSlider;
    Dial mixSlider;
    NameLabel rateLabel;
    NameLabel depthLabel;
    NameLabel centerDelayLabel;
    NameLabel fdbkLabel;
    NameLabel mixLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> centerDelaySliderAttachment;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>fdbkSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChorusComponent)
};
