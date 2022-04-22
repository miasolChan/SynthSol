

#pragma once

#include <JuceHeader.h>
#include"LookAndFeel/Dial.h"
#include"LookAndFeel/NameLabel.h"
#include"LookAndFeel/CustomColours.h"
//==============================================================================
/*
*/
class PhaserComponent  : public juce::Component
{
public:
    PhaserComponent(juce::AudioProcessorValueTreeState& apvts, juce::String rateID,
        juce::String depthID, juce::String centerFreqID, juce::String fdbkID, juce::String mixID);
    ~PhaserComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text);
    Dial rateSlider;
    Dial depthSlider;
    Dial centerFreqSlider;
    Dial fdbkSlider;
    Dial mixSlider;
    NameLabel rateLabel;
    NameLabel depthLabel;
    NameLabel centerFreqLabel;
    NameLabel fdbkLabel;
    NameLabel mixLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rateSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> centerFreqSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fdbkSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> mixSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PhaserComponent)
};
