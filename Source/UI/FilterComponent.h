

#pragma once

#include <JuceHeader.h>
#include"LookAndFeel/Dial.h"
#include"LookAndFeel/NameLabel.h"
#include"LookAndFeel/CustomColours.h"
//==============================================================================
/*
*/
class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String lowCutFreq,
        juce::String highCutFreq, juce::String peakFreq, juce::String peakGain, juce::String peakQuality, juce::String lowCutSlope, juce::String highCutSlope);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:

    //low/high/peak freq
    juce::Slider lowCutFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> lowCutFreqAttachment;

    juce::Slider peakFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakFreqAttachment;

    juce::Slider highCutFreqSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> highCutFreqAttachment;

    //peakgain ´¹Ö±
    juce::Slider peakGainSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakGainAttachment;

    //peakQuality
    juce::Slider peakQualitySlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> peakQualityAttachment;

    //slope
    juce::ComboBox highSlopeBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> highSlopeAttachment;
    juce::ComboBox lowSlopeBox;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> lowSlopeBoxAttachment;

    //Lable
    juce::Label lowFreqLabel;
    juce::Label peakFreqLabel;
    juce::Label highFreqLabel;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    void setNomalSlider(juce::AudioProcessorValueTreeState& apvts, juce::Slider& slider, juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment,int type);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};
