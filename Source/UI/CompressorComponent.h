

#pragma once

#include <JuceHeader.h>
#include"LookAndFeel/Dial.h"
#include"LookAndFeel/NameLabel.h"
#include"LookAndFeel/CustomColours.h"
//==============================================================================
/*
*/
class CompressorComponent  : public juce::Component
{
public:
    CompressorComponent(juce::AudioProcessorValueTreeState& apvts, juce::String thresholdID,
        juce::String ratioID, juce::String attackID, juce::String releaseID);
    ~CompressorComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text);

    Dial thresholdSlider;
    Dial ratioSlider;
    Dial attackSlider;
    Dial releaseSlider;
    NameLabel thresholdLabel;
    NameLabel ratioLabel;
    NameLabel attackLabel;
    NameLabel releaseLabel;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> ratioSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> attackSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> releaseSliderAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorComponent)
};
