

#pragma once

#include <JuceHeader.h>
#include"LookAndFeel/Dial.h"
#include"LookAndFeel/NameLabel.h"
#include"LookAndFeel/CustomColours.h"
//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveID, juce::String fmFreqID,
        juce::String fmDepthID, juce::String  fmPitchID, juce::String fmGainID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
private:

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment, juce::String text);

    juce::ComboBox waveformSelector;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

    NameLabel waveformLabel;

    Dial fmFrequencySlider;
    Dial fmDepthSlider;
    Dial fmPitchSlider;
    Dial fmGainSlider;

    NameLabel fmFrequencyLabel;
    NameLabel fmDepthLabel;
    NameLabel fmPitchLabel;
    NameLabel fmGainLabel;

    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmFrequencySliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmDepthSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmPitchSliderAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> fmGainSliderAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
